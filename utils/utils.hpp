#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	template <class T>
	struct remove_const
	{
		typedef T	type;
	};

	template <class T>
	struct remove_const<const T>
	{
		typedef T	type;
	};

	template <bool Cond, class T = void>
	struct enable_if;

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned short>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long>
	{
		static const bool value = true;
	};

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 != *first2)
				return (*first1 < *first2);
			first1++;
			first2++;
		}
		return (first1 == last1 && first2 != last2);
	}

	template <class T1, class T2>
	struct pair
	{
		public:
			typedef	T1	first_type;
			typedef	T2	second_type;

			first_type	first;
			second_type	second;
		
			pair() : first(), second() {}
			template<class U, class V>
			pair(const pair<U,V> & pr) : first(pr.first), second(pr.second) {}
			pair(const first_type & a, const second_type & b) : first(a), second(b) {}
			~pair() {}

			pair & operator= (const pair & pr)
			{
				if (this == &pr)
					return (*this);
				first = pr.first;
				second = pr.second;
				return (*this);
			}
	};

	template <class _T1, class _T2>
	bool operator== (const pair<_T1,_T2> & lhs, const pair<_T1,_T2> & rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class _T1, class _T2>
	bool operator!= (const pair<_T1,_T2> & lhs, const pair<_T1,_T2> & rhs)
	{
		return !(lhs == rhs);
	}

	template <class _T1, class _T2>
	bool operator< (const pair<_T1,_T2> & lhs, const pair<_T1,_T2> & rhs)
	{
		if (lhs.first != rhs.first)
			return (lhs.first < rhs.first);
		if (lhs.second != rhs.second)
			return (lhs.second < rhs.second);
		return (false);
	}

	template <class _T1, class _T2>
	bool operator<= (const pair<_T1,_T2> & lhs, const pair<_T1,_T2> & rhs)
	{
		return !(rhs < lhs);
	}

	template <class _T1, class _T2>
	bool operator> (const pair<_T1,_T2> & lhs, const pair<_T1,_T2> & rhs)
	{
		return (rhs < lhs);
	}

	template <class _T1, class _T2>
	bool operator>= (const pair<_T1,_T2> & lhs, const pair<_T1,_T2> & rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class T>
	T length(T n)
	{
		T	len;

		len = 1;
		if (n < 0)
		{
			n *= -1;
			len++;
		}
		n = n / 10;
		while (n > 0)
		{
			len++;
			n = n / 10;
		}
		return (len);
	}

	template <class T>
	std::string fill(T n, T len)
	{
		int	i;
		std::string	res(len, 0);

		i = len - 1;
		if (n >= 0)
		{
			while (i >= 0)
			{
				res[i] = (n % 10) + 48;
				n = n / 10;
				i--;
			}
		}
		else
		{
			n *= -1;
			res[0] = '-';
			while (i > 0)
			{
				res[i] = (n % 10) + 48;
				n = n / 10;
				i--;
			}
		}
		return (res);
	}

	template <class T>
	std::string itoa(T n)
	{
		T			len;
		std::string	res;

		if (n == (T)-2147483648)
		{
			res = fill(n + 1, (T)11);
			res[10] = '8';
			return (res);
		}
		len = length(n);
		res = fill(n, len);
		return (res);
	}
}

#endif
