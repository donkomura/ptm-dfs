#ifndef _RPC_H_
#define _RPC_H_

void
rpc_kv_write(const thallium::request& req, const std::string& key, const std::string& value);

void
rpc_kv_read(const thallium::request& req, const std::string& key, size_t& value_size);

void
rpc_kv_remove(const thallium::request& req, const std::string& key);
#endif // _RPC_H_
