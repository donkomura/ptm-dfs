#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include "rpc.hpp"
#include "type.hpp"
#include "kv.hpp"

void
rpc_kv_write(const thallium::request& req, const std::string& key, const std::string& value)
{
	kv_put(key, key.size(), value, value.size());
	req.respond(RPC_OK);
}

void
rpc_kv_read(const thallium::request& req, const std::string& key, size_t& value_size)
{
	std::cout << "read called on key=" << key << std::endl;
	fs_read_result<std::string> res;
	std::string value(value_size, '.');
	kv_get(key, key.size(), value, value_size);
	res.data() = value;
	req.respond(res);
}
