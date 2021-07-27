#ifndef _TYPE_H_
#define _TYPE_H_

#include "kv.hpp"
#include "kv_err.hpp"
#include "rpc.hpp"

class kv_write_result {
	public:
		kv_write_result() = default;
		kv_write_result(kv_write_result&&) = default;
		kv_write_result(const kv_write_result&) = default;
		kv_write_result& operator=(kv_write_result&&) = default;
		kv_write_result& operator=(const kv_write_result&) = default;

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
class kv_read_result {
	public:
		kv_read_result() = default;
		kv_read_result(kv_read_result&&) = default;
		kv_read_result(const kv_read_result&) = default;
		kv_read_result& operator=(kv_read_result&&) = default;
		kv_read_result& operator=(const kv_read_result&) = default;

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

class kv_remove_result : public kv_write_result {
	private:
		kv_status _err = KV_SUCCESS;
};

#endif // _TYPE_H_
