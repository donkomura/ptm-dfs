#ifndef _KV_H_
#define _KV_H_

using kv_status = int;

void kv_init(const std::string& path, size_t db_size);
void kv_term();

kv_status kv_put(const std::string& key, size_t key_size, const std::string& value, size_t value_size);
kv_status kv_get(const std::string& key, size_t key_size, std::string& value, size_t& value_size);
kv_status kv_remove(const std::string& key, size_t key_size);

#endif // _KV_H_
