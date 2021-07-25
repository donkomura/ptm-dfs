void kv_init(const std::string& path, size_t db_size);
void kv_term();

template <typename T>
void kv_put(const std::string& key, size_t key_size, const T& value, size_t value_size);

void *kv_get(const std::string& key, size_t key_size);
