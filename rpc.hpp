#ifndef _RPC_H_
#define _RPC_H_

using rpc_return_t = int;

#define RPC_BASE_X		10000
#define RPC_CODE(x)		(RPC_BASE_X + x)
#define RPC_OK		(RPC_CODE(0))
#define RPC_EPERM		(RPC_CODE(1))
#define RPC_ENOENT		(RPC_CODE(2))
#define RPC_UNKNOWN		(RPC_CODE(10))

void
rpc_kv_write(const thallium::request& req, const std::string& key, const std::string& value);

void
rpc_kv_read(const thallium::request& req, const std::string& key, size_t& value_size);

#endif // _RPC_H_
