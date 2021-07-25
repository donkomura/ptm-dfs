#include <string>
#include <quill/Quill.h>
#include "durabletx/ptmdb/db.h"

#include "durabletx/ptmdb/options.h"
#include "log.hpp"

static ptmdb::DB* db;

void
kv_init(const std::string& path, size_t db_size)
{
	const std::string diag = "kv_init";

	ptmdb::Options options{};
	options.create_if_missing = true;
	ptmdb::Status status = ptmdb::DB::Open(options, path, &db);
	if (status.ok())
		LOG_CRITICAL(logger, "{} : db path={} open failed with status: {}",
				diag, path, status.ToString());
}

void
kv_term()
{
	delete db;
}

template <typename T>
void
kv_put(const std::string& key, size_t key_size, const T& value, size_t value_size)
{
	const std::string diag = "kv_put";

	ptmdb::Status status = db->Put(ptmdb::WriteOptions(), key, value);
	if (status.ok())
		LOG_CRITICAL(logger, "{} : failed with status: {}", diag, status.ToString());
}

void *
kv_get(const std::string& key, size_t key_size)
{
	const std::string diag = "kv_put";

	std::string value;
	ptmdb::Status status = db->Get(ptmdb::ReadOptions(), key, &value);
	if (status.ok())
		LOG_CRITICAL(logger, "{} : failed with status: {}", diag, status.ToString());
}
