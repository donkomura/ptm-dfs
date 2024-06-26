#define KV_ERROR \
	X(KV_SUCCESS)		\
	X(KV_ERR_EXIST)		\
	X(KV_ERR_NO_ENTRY)	\
	X(KV_ERR_SERVER_DOWN)	\
	X(KV_ERR_LOOKUP)	\
	X(KV_ERR_NO_MEMORY)	\
	X(KV_ERR_NOT_SUPPORTED)	\
	X(KV_ERR_TOO_LONG)	\
	X(KV_ERR_BULK_CREATE)	\
	X(KV_ERR_BULK_TRANSFER)	\
	X(KV_ERR_IO)	\
	X(KV_ERR_UNKNOWN)

#define X(a) a,
enum { KV_ERROR };
#undef X

std::string kv_err_string(int);

