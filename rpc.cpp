#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <quill/Quill.h>
#include "rpc.hpp"
#include "type.hpp"
#include "kv.hpp"
#include "log.hpp"

void
rpc_kv_write(const thallium::request& req, const std::string& key, const std::string& value)
{
	fs_write_result res;
	kv_status s;

	s = kv_put(key, key.size(), value, value.size());
	res.err() = s;
	req.respond(res);
}

void
rpc_kv_read(const thallium::request& req, const std::string& key, size_t& value_size)
{
	fs_read_result<std::string> res;
	std::string value = std::string(value_size, '.');
	kv_status s;

	s = kv_get(key, key.size(), value, value_size);
	res.data() = value;
	res.err() = s;
	req.respond(res);
}

void
rpc_remove(const thallium::request& req, const std::string& key)
{
	fs_remove_result res;
	kv_status s;
	
	s = kv_remove(key, key.size());
	res.err() = s;
	req.respond(res);
}
