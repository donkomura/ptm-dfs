#include <iostream>
#include <string>
#include <thallium.hpp>
#include <thallium/remote_procedure.hpp>
#include <thallium/serialization/stl/vector.hpp>
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
	thallium::remote_procedure fs_write = engine.define("fs_write");
	thallium::remote_procedure fs_read = engine.define("fs_read");
	std::string key = "key", value = "value";
	rpc_return_t ret = fs_write.on(server)(key, key.size(), value, value.size());
	std::cout << "fs_write:ret=" << ret << std::endl;
	fs_read_result<std::vector<unsigned char>> read_val = 
		fs_read.on(server)(key, key.size());
	std::cout << "fs_read: ret="
		<< std::string(read_val.data().begin(), read_val.data().end())
		<< std::endl;

	return 0;
}
