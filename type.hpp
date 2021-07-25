#include <thallium/serialization/stl/string.hpp>

template <typename T>
class fs_read_result {
	public:
		fs_read_result() = default;
		fs_read_result(fs_read_result&&) = default;
		fs_read_result(const fs_read_result&) = default;
		/* prevent copy initialization */
		fs_read_result& operator=(fs_read_result&&) = default;
		fs_read_result& operator=(const fs_read_result&) = default;

		template <typename A>
		void serialize(A& a)
		{
			a & _data;
		}

		T& data() {
			return _data;
		}

		const T& data() const {
			return _data;
		}

	private:
		T _data;
};

