#include <string>
#include <quill/Quill.h>
#include "durabletx/ptmdb/db.h"

#include "kv.hpp"
#include "kv_err.hpp"
#include "log.hpp"

static ptmdb::DB* db;

static inline kv_status
kv_err(ptmdb::Status s)
{
	if (s.ok())
		return (KV_SUCCESS);
	else if (s.IsNotFound())
		return (KV_ERR_NO_ENTRY);
	else if (s.IsNotSupportedError())
		return (KV_ERR_NOT_SUPPORTED);
	else if (s.IsIOError())
		return (KV_ERR_IO);
	else if (s.IsCorruption())
		return (KV_ERR_SERVER_DOWN);
	else
		return (KV_ERR_UNKNOWN);
}

void
kv_init(const std::string& path, size_t db_size)
{
	const std::string diag = "kv_init";
	auto l = get_logger();
	LOG_INFO(l, "{} : path={}, size={}", diag, path, db_size);

	ptmdb::Options options{};
	options.create_if_missing = true;
	ptmdb::Status status = ptmdb::DB::Open(options, path, &db);
	if (!status.ok())
		LOG_ERROR(l, "{} : db path = {} open failed with status: {}",
				diag, path, status.ToString());
}

void
kv_term()
{
	delete db;
}

kv_status
kv_put(const std::string& key, size_t key_size, const std::string& value, size_t value_size)
{
	const std::string diag = "kv_put";
	auto l = get_logger();

	ptmdb::Status status = db->Put(ptmdb::WriteOptions(), key, value);
	if (!status.ok()) {
		LOG_ERROR(l, "{} : failed with status: {}", diag, status.ToString());
		return kv_err(status);
	}

	return (KV_SUCCESS);
}

kv_status
kv_get(const std::string& key, size_t key_size, std::string& value, size_t& value_size)
{
	const std::string diag = "kv_get";
	auto l = get_logger();

	ptmdb::Status status = db->Get(ptmdb::ReadOptions(), key, &value);
	if (!status.ok()) {
		LOG_ERROR(l, "{} : failed with status: {}", diag, status.ToString());
		return kv_err(status);
	} else {
		value_size = value.size();
	}

	return (KV_SUCCESS);
}

kv_status
kv_remove(const std::string& key, size_t key_size)
{
	const std::string diag = "kv_remove";
	auto l = get_logger();

	ptmdb::Status status = db->Delete(ptmdb::WriteOptions(), key);
	if (!status.ok()) {
		LOG_ERROR(l, "{} : failed with status: {}", diag, status.ToString());
		return kv_err(status);
	}

	return (KV_SUCCESS);
}
