#include <thallium.hpp>
#include "rpc.hpp"
#include "type.hpp"

void
fs_write(const thallium::request& req, const std::string& key, const size_t key_size,
		const std::string& value, const size_t value_size)
{
	req.respond(RPC_OK);
}

void
fs_read(const thallium::request& req, const std::string& key, const size_t key_size)
{
	std::cout << "read called on key=" << key << std::endl;
	std::string value = "this is result value for key " + key;
	fs_read_result<std::string> res;
	res.data() = value;
	req.respond(res);
}
