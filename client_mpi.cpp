#include <iostream>
#include <string>
#include <thallium.hpp>
#include <thallium/remote_procedure.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "rpc.hpp"
#include "type.hpp"

namespace bm = boost::mpi;

int
main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " address" << std::endl;
		exit(0);
	}

	bm::environment env(argc, argv);
	bm::communicator world;

	std::cout << "rank: " << world.rank() << std::endl;

	thallium::engine engine("tcp", THALLIUM_CLIENT_MODE);
	thallium::endpoint server = engine.lookup(argv[1]);
	thallium::remote_procedure rpc_kv_write = engine.define("rpc_kv_write");
	thallium::remote_procedure rpc_kv_read = engine.define("rpc_kv_read");

	std::string key = "key_" + std::to_string(world.rank()),
		value = "value_" + std::to_string(world.rank());
	kv_write_result ret = rpc_kv_write.on(server)(key, value);
	std::cout << "rpc_kv_write:ret=" << ret.err() << std::endl;

	std::string buf = std::string(value.size(), '_');
	size_t buf_size = buf.size();
	kv_read_result<std::string> read_val = 
		rpc_kv_read.on(server)(key, buf_size);
	std::cout << "rpc_kv_read: key=" << key << ",value="
		<< std::string(read_val.data().begin(), read_val.data().end())
		<< std::endl;

	return 0;
}
