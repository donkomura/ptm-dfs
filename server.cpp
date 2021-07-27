#include <iostream>
#include <csignal>
#include <thread>
#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <boost/program_options.hpp>
#include <quill/Quill.h>
#include "rpc.hpp"
#include "log.hpp"
#include "kv.hpp"

#define PMEMPOOL "/tmp/ptm.db"
#define DB_SIZE 256*1024*1024
#define NTHREAD 1
#define LOGLEVEL "Info"
#define LOGFILE "ptmdb_dfs.log"

#define FAIL(fmt, ...)			\
do {			\
	fprintf(stderr, fmt " aborting\n", ## __VA_ARGS__); \
	exit(1);			\
} while (0);

#define ASSERT(cond, ...)			\
do {			\
	if (!(cond))			\
		FAIL(__VA_ARGS__);			\
} while (0);

struct options {
	std::string pool_path, log_level, log_file;
	size_t db_size, nthread;
} ops;

int
set_options(boost::program_options::variables_map vm)
{
	try {
		ops.pool_path = vm["pool"].as<std::string>();
		ops.db_size = vm["db_size"].as<size_t>();
		ops.nthread = vm["thread"].as<size_t>();
		ops.log_level = vm["log_level"].as<std::string>();
		ops.log_file = vm["log_file"].as<std::string>();
	} catch(const boost::bad_any_cast& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

void *
handle_sig(void *arg)
{
	sigset_t *s = (sigset_t *)arg;
	int sig;

	sigwait(s, &sig);
	kv_term();
	exit(1);
}

int
main(int argc, char **argv)
{
	static sigset_t sigset;
	pthread_t pt;
	std::string address;
	int rc;

	/* options */
	using namespace boost::program_options;
	variables_map vm;

	options_description description("PTM-DFS : persistent transactional memory model dfs");
	description.add_options()
		("help,h", "print this description")
		("pool,p", value<std::string>()->default_value(PMEMPOOL), "pmem pool path")
		("db_size,s", value<size_t>()->default_value(DB_SIZE), "db size for ptmdb")
		("thread,t", value<size_t>()->default_value(NTHREAD), "thread count")
		("log_level,l", value<std::string>()->default_value(LOGLEVEL), 
			 "logging level [Debug, Info, Warning, Error, Critical]")
		("log_file,L", value<std::string>()->default_value(LOGFILE),
			 "logging to file")
		("debug,d", "log output to console")
		;

	try {
		store(parse_command_line(argc, argv, description), vm);
	} catch (const error_with_option_name& e) {
		std::cout << e.what() << std::endl;
		exit(1);
	}
	notify(vm);

	if (vm.count("help")) {
		std::cout << description << std::endl;
		exit(0);
	}

	rc = set_options(vm);
	ASSERT(rc == 0, "set_options failed");

	/**
	 * sigwait thread prepare
	 * we use pthread only for singnal handle 
	 * about mix std::thread/pthread, see https://stackoverflow.com/a/54871996
	 */
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGTERM);
	pthread_sigmask(SIG_BLOCK, &sigset, NULL);
	pthread_create(&pt, NULL, handle_sig, &sigset);
	pthread_detach(pt);

	/* setup logger */
	quill::Logger* logger;
	quill::start();
	if (vm.count("debug")) {
		quill::Handler* stdout_handle = quill::stdout_handler("stdout_main");
		stdout_handle->set_log_level(quill::from_string(ops.log_level));
		logger = quill::create_logger("logger", stdout_handle);
	} else {
		quill::Handler* file_handle = quill::file_handler(ops.log_file, "w");
		file_handle->set_log_level(quill::from_string(ops.log_level));
		logger = quill::create_logger("logger", file_handle);
	}

	thallium::engine engine("tcp", THALLIUM_SERVER_MODE, 1, ops.nthread);
	address = engine.self();
	LOG_INFO(logger, "server status at address {}", address);

	kv_init(ops.pool_path, ops.db_size);

	engine.define("rpc_kv_write", rpc_kv_write);
	engine.define("rpc_kv_read", rpc_kv_read);

	/* finalize thallium */
	engine.enable_remote_shutdown();
	engine.wait_for_finalize();
}
