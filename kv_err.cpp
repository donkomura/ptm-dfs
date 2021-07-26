#include "kv_err.hpp"

#define X(a) #a,
static std::string kv_error_list[] = { KV_ERROR };
#undef X

std::string
kv_err_string(int err)
{
	if (err < 0 || err > KV_ERR_UNKNOWN)
		err = KV_ERR_UNKNOWN;
	return (kv_error_list[err]);
}

