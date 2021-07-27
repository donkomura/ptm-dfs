#include <quill/detail/LogMacros.h>
#include <thallium.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <quill/Quill.h>
#include <shared_mutex>
#include "rpc.hpp"
#include "type.hpp"
#include "kv.hpp"
#include "log.hpp"

std::shared_timed_mutex grwlock {};

void
rpc_kv_write(const thallium::request& req, const std::string& key, const std::string& value)
{
	kv_write_result res;
	kv_status s;
	auto l = get_logger();
	std::string diag = "rpc_kv_write";
	LOG_INFO(l, "{} : key={}", diag, key);

	grwlock.lock();
	s = kv_put(key, key.size(), value, value.size());
	grwlock.unlock();

	res.err() = s;
	req.respond(res);
}

void
rpc_kv_read(const thallium::request& req, const std::string& key, size_t& value_size)
{
	kv_read_result<std::string> res;
	std::string value = std::string(value_size, '.');
	kv_status s;
	auto l = get_logger();
	std::string diag = "rpc_kv_read";
	LOG_INFO(l, "{} : key={}", diag, key);

	grwlock.lock();
	s = kv_get(key, key.size(), value, value_size);
	grwlock.unlock();

	res.data() = value;
	res.err() = s;
	req.respond(res);
}

void
rpc_remove(const thallium::request& req, const std::string& key)
{
	kv_remove_result res;
	kv_status s;
	auto l = get_logger();
	std::string diag = "rpc_kv_remove";
	LOG_INFO(l, "{} : key={}", diag, key);
	
	grwlock.lock();
	s = kv_remove(key, key.size());
	grwlock.unlock();

	res.err() = s;
	req.respond(res);
}
