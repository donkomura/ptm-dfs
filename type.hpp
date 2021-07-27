#ifndef _TYPE_H_
#define _TYPE_H_

#include "kv.hpp"
#include "kv_err.hpp"
#include "rpc.hpp"

class fs_write_result {
	public:
		fs_write_result() = default;
		fs_write_result(fs_write_result&&) = default;
		fs_write_result(const fs_write_result&) = default;
		fs_write_result& operator=(fs_write_result&&) = default;
		fs_write_result& operator=(const fs_write_result&) = default;

		template <typename A>
		void serialize(A& a)
		{
			a & _err;
		}

		kv_status& err() { return _err; }
		const kv_status& err() const { return _err; }

	private:
		kv_status _err = KV_SUCCESS;
};

template <typename T>
class fs_read_result {
	public:
		fs_read_result() = default;
		fs_read_result(fs_read_result&&) = default;
		fs_read_result(const fs_read_result&) = default;
		fs_read_result& operator=(fs_read_result&&) = default;
		fs_read_result& operator=(const fs_read_result&) = default;

		template <typename A>
		void serialize(A& a)
		{
			a & _data;
			a & _err;
		}

		T& data() { return _data; }
		const T& data() const { return _data; }
		kv_status& err() { return _err; }
		const kv_status& err() const { return _err; }

	private:
		T 		_data;
		kv_status 	_err = KV_SUCCESS;
};

class fs_remove_result : public fs_write_result {
	private:
		kv_status _err = KV_SUCCESS;
};

#endif // _TYPE_H_
