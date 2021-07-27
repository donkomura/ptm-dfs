#include <iostream>
#include <string>
#include <thallium.hpp>
#include <thallium/remote_procedure.hpp>
#include <thallium/serialization/stl/string.hpp>
#include "rpc.hpp"
#include "type.hpp"

int
main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " address" << std::endl;
		exit(0);
	}

	thallium::engine engine("tcp", THALLIUM_CLIENT_MODE);
	thallium::endpoint server = engine.lookup(argv[1]);
	thallium::remote_procedure rpc_kv_write = engine.define("rpc_kv_write");
	thallium::remote_procedure rpc_kv_read = engine.define("rpc_kv_read");
	std::string key = "key_0", value = "value_0";
	int ret = rpc_kv_write.on(server)(key, value);
	std::cout << "rpc_kv_write:ret=" << ret << std::endl;

	std::string buf = std::string(value.size(), '_');
	size_t buf_size = buf.size();
	fs_read_result<std::string> read_val = 
		rpc_kv_read.on(server)(key, buf_size);
	std::cout << "rpc_kv_read: ret="
		<< std::string(read_val.data().begin(), read_val.data().end())
		<< std::endl;

	return 0;
}
