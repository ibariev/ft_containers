#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "../utils/iterator.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef random_access_iterator<T>					iterator;
		typedef random_access_iterator<const T>				const_iterator;
		typedef Reverse_iterator<iterator>					reverse_iterator;
		typedef Reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef size_t										size_type;

	private:
		value_type *	_array;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;
	
	public:
		explicit vector(const allocator_type & alloc = allocator_type());
		explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0);
		vector(const vector & x);
		~vector();
		vector & operator= (const vector & x);

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		
		size_type size() const;
		size_type max_size() const;
		void resize(size_type n, value_type val = value_type());
		size_type capacity() const;
		bool empty() const;
		void reserve(size_type n);

		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
		reference at(size_type n);
		const_reference at(size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		template <class InputIterator>
		void assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last);
		void assign(size_type n, const value_type & val);
		void push_back(const value_type & val);
		void pop_back();
		iterator insert(iterator position, const value_type & val);
		void insert(iterator position, size_type n, const value_type & val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type * = 0);
		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);
		void swap(vector & x);
		void clear();

		allocator_type get_allocator() const;

		template <class _T, class _Alloc>
		friend bool operator== (const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs);
		template <class _T, class _Alloc>
		friend bool operator!= (const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs);
		template <class _T, class _Alloc>
		friend bool operator< (const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs);
		template <class _T, class _Alloc>
		friend bool operator<= (const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs);
		template <class _T, class _Alloc>
		friend bool operator> (const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs);
		template <class _T, class _Alloc>
		friend bool operator>= (const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs);
		template <class _T, class _Alloc>
		friend void swap (vector<_T, _Alloc> & x, vector<_T, _Alloc> & y);
};

template <class T, class Alloc>
vector<T, Alloc>::vector(const vector<T, Alloc>::allocator_type & alloc)
{
	_size = 0;
	_capacity = 0;
	_alloc = alloc;
	_array = NULL;
}

template <class T, class Alloc>
vector<T, Alloc>::vector(vector<T, Alloc>::size_type n, const vector<T, Alloc>::value_type & val, const vector<T, Alloc>::allocator_type & alloc)
{
	_size = n;
	_capacity = n;
	_alloc = alloc;
	_array = _alloc.allocate(n);
	for (vector<T, Alloc>::size_type i = 0; i < n; i++)
		_alloc.construct(_array + i, val);
}

template <class T, class Alloc>
template <class InputIterator>
vector<T, Alloc>::vector(InputIterator first, InputIterator last, const vector<T, Alloc>::allocator_type & alloc, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *)
{
	_size = last - first;
	_capacity = _size;
	_alloc = alloc;
	_array = _alloc.allocate(_capacity);
	for (vector<T, Alloc>::size_type i = 0; i < _size; i++)
		_alloc.construct(_array + i, *(first + i));
}

template <class T, class Alloc>
vector<T, Alloc>::vector(const vector<T, Alloc> & x)
{
	_size = x._size;
	_capacity = x._capacity;
	_alloc = x._alloc;
	_array = _alloc.allocate(_size);
	for (vector<T, Alloc>::size_type i = 0; i < _size; i++)
		_alloc.construct(_array + i, *(x._array + i));
}

template <class T, class Alloc>
vector<T, Alloc>::~vector()
{
	for (vector<T, Alloc>::size_type i = 0; i < _size; i++)
		_alloc.destroy(_array + i);
	if (_array)
		_alloc.deallocate(_array, _capacity);
}

template <class T, class Alloc>
vector<T, Alloc> & vector<T, Alloc>::operator= (const vector<T, Alloc> & x)
{
	if (this == &x)
		return (*this);
	if (x._capacity > _capacity && x._size > _size)
		vector<T, Alloc>::reserve(x._capacity);
	for (vector<T, Alloc>::size_type i = x._size; i < _size; i++)
		_alloc.destroy(_array + i);
	for (vector<T, Alloc>::size_type i = _size; i < x._size; i++)
		_alloc.construct(_array + i, *(x._array + i));
	for (vector<T, Alloc>::size_type i = 0; i < x._size; i++)
		_array[i] = x._array[i];
	_size = x._size;
	return (*this);
}

template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
{
	return (_size);
}

template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
{
	return (_alloc.max_size());
}

template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
{
	return (_capacity);
}

template <class T, class Alloc>
bool vector<T, Alloc>::empty() const
{
	return (_size == 0);
}

template <class T, class Alloc>
void vector<T, Alloc>::reserve(vector<T, Alloc>::size_type n)
{
	if (n > _alloc.max_size())
		throw std::length_error("vector::reserve");
	if (n > _capacity)
	{
		vector<T, Alloc>::value_type * newarr = _alloc.allocate(n);
		vector<T, Alloc>::size_type i;
		try
		{
			for (i = 0; i < _size; i++)
				_alloc.construct(newarr + i, *(_array + i));
		}
		catch (...)
		{
			for (vector<T, Alloc>::size_type j = 0; j < i; j++)
				_alloc.destroy(newarr + j);
			_alloc.deallocate(newarr, n);
			throw ;
		}
		for (vector<T, Alloc>::size_type i = 0; i < _size; i++)
			_alloc.destroy(_array + i);
		if (_array)
			_alloc.deallocate(_array, _capacity);
		_array = newarr;
		_capacity = n;
	}
}

template <class T, class Alloc>
void vector<T, Alloc>::resize(vector<T, Alloc>::size_type n, vector<T, Alloc>::value_type val)
{
	if (n < _size)
	{
		for (vector<T, Alloc>::size_type i = n; i < _size; i++)
			_alloc.destroy(_array + i);
	}
	else if (n > _size)
	{
		vector<T, Alloc>::size_type cap = _capacity;
		try
		{
			if (n > _capacity)
			{
				if (2 * _capacity > n)
					vector<T, Alloc>::reserve(2 * _capacity);
				else
					vector<T, Alloc>::reserve(n);
			}
		}
		catch(const std::length_error & e)
		{
			throw std::length_error("vector::_M_default_append");
		}
		vector<T, Alloc>::size_type i;
		try
		{
			for (i = _size; i < n; i++)
				_alloc.construct(_array + i, val);
		}
		catch (...)
		{
			for (vector<T, Alloc>::size_type j = _size; j < i; j++)
				_alloc.destroy(_array + j);
			if (n > cap)
				_alloc.deallocate(_array + cap, n - cap);
			_capacity = cap;
			throw ;
		}
	}
	_size = n;
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[] (vector<T, Alloc>::size_type n)
{
	return (_array[n]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[] (vector<T, Alloc>::size_type n) const
{
	return (_array[n]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(vector<T, Alloc>::size_type n)
{
	if (n >= _size)
	{
		std::string what;

		what = "vector::_M_range_check: __n (which is " + ft::itoa(n);
		what += ") >= this->size() (which is " + ft::itoa(_size) + ")";
		throw std::out_of_range(what);
	}
	return (_array[n]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(vector<T, Alloc>::size_type n) const
{
	if (n >= _size)
	{
		std::string what;

		what = "vector::_M_range_check: __n (which is " + ft::itoa(n);
		what += ") >= this->size() (which is " + ft::itoa(_size) + ")";
		throw std::out_of_range(what);
	}
	return (_array[n]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front()
{
	return (_array[0]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const
{
	return (_array[0]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back()
{
	return (_array[_size - 1]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
{
	return (_array[_size - 1]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const
{
	return (_alloc);
}

template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
{
	vector<T, Alloc>::size_type	n = last - first;
	
	if (n > _alloc.max_size())
		throw std::length_error("cannot create ft::vector larger than max_size()");
	this->clear();
	if (n > _capacity)
		this->reserve(n);
	vector<T, Alloc>::size_type i;
	try
	{
		for (i = 0; i < n; i++)
			_alloc.construct(_array + i, *(first + i));
	}
	catch (...)
	{
		for (vector<T, Alloc>::size_type j = 0; j < i; j++)
			_alloc.destroy(_array + j);
		throw ;
	}
	_size = n;
}

template <class T, class Alloc>
void vector<T, Alloc>::assign (vector<T, Alloc>::size_type n, const vector<T, Alloc>::value_type & val)
{
	if (n > _alloc.max_size())
		throw std::length_error("cannot create ft::vector larger than max_size()");
	this->clear();
	if (n > _capacity)
		this->reserve(n);
	vector<T, Alloc>::size_type i;
	try
	{
		for (i = 0; i < n; i++)
			_alloc.construct(_array + i, val);
	}
	catch (...)
	{
		for (vector<T, Alloc>::size_type j = 0; j < i; j++)
			_alloc.destroy(_array + j);
		throw ;
	}
	_size = n;
}

template <class T, class Alloc>
void vector<T, Alloc>::push_back(const vector<T, Alloc>::value_type & val)
{
	vector<T, Alloc>::resize(_size + 1, val);	
}

template <class T, class Alloc>
void vector<T, Alloc>::pop_back()
{
	if (_size)
		vector<T, Alloc>::resize(_size - 1);
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, const vector<T, Alloc>::value_type & val)
{
	vector<T, Alloc>::size_type i = position - this->begin();
	try
	{
		if (_size + 1 > _capacity)
		{
			if (2 * _capacity > _size + 1)
				vector<T, Alloc>::reserve(2 * _capacity);
			else
				vector<T, Alloc>::reserve(_size + 1);
		}
	}
	catch (const std::length_error & e)
	{
		throw std::length_error("vector::_M_default_append");
	}
	for (vector<T, Alloc>::size_type j = _size; j > i; j--)
		_alloc.construct(_array + j, _array[j - 1]);
	_alloc.construct(_array + i, val);
	_size += 1;
	return (vector<T, Alloc>::iterator(_array + i));
}

template <class T, class Alloc>
void vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, vector<T, Alloc>::size_type n, const vector<T, Alloc>::value_type & val)
{
	vector<T, Alloc>::size_type i = position - this->begin();
	try
	{
		if (_size + n > _capacity)
		{
			if (2 * _capacity > _size + n)
				vector<T, Alloc>::reserve(2 * _capacity);
			else
				vector<T, Alloc>::reserve(_size + n);
		}
	}
	catch (const std::length_error & e)
	{
		throw std::length_error("vector::_M_default_append");
	}
	for (vector<T, Alloc>::size_type j = _size + n - 1; j >= i + n; j--)
		_alloc.construct(_array + j, _array[j - n]);
	for (vector<T, Alloc>::size_type k = 0; k < n; i++, k++)
		_alloc.construct(_array + i, val);
	_size += n;
}

template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type *)
{
	vector<T, Alloc>::size_type	n = last - first;
	vector<T, Alloc>::size_type i = position - this->begin();
	try
	{
		if (_size + n > _capacity)
		{
			if (2 * _capacity > _size + n)
				vector<T, Alloc>::reserve(2 * _capacity);
			else
				vector<T, Alloc>::reserve(_size + n);
		}
	}
	catch (const std::length_error & e)
	{
		throw std::length_error("vector::_M_default_append");
	}
	for (vector<T, Alloc>::size_type j = _size + n - 1; j >= i + n; j--)
		_alloc.construct(_array + j, _array[j - n]);
	for (vector<T, Alloc>::size_type k = 0; k < n; i++, k++)
		_alloc.construct(_array + i, *(first + k));
	_size += n;
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector<T, Alloc>::iterator position)
{
	vector<T, Alloc>::size_type i = position - this->begin();
	for ( ; i < _size - 1; i++)
		_array[i] = _array[i + 1];
	_alloc.destroy(_array + _size - 1);
	_size -= 1;
	return (position);
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector<T, Alloc>::iterator first, vector<T, Alloc>::iterator last)
{
	vector<T, Alloc>::size_type i = first - this->begin();
	vector<T, Alloc>::size_type n = last - first;
	for ( ; i < _size - n; i++)
		_array[i] = _array[i + n];
	for (i = _size - n; i < _size; i++)
		_alloc.destroy(_array + i);
	_size -= n;
	return (first);
}

template <class T, class Alloc>
void vector<T, Alloc>::swap(vector<T, Alloc> & x)
{
	if (this == &x)
		return ;
	std::swap(_array, x._array);
	std::swap(_size, x._size);
	std::swap(_capacity, x._capacity);
	std::swap(_alloc, x._alloc);
}

template <class T, class Alloc>
void vector<T, Alloc>::clear()
{
	vector<T, Alloc>::resize(0);
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin()
{
	return (vector<T, Alloc>::iterator(_array));

}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const
{
	return (vector<T, Alloc>::const_iterator(_array));
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end()
{
	return (vector<T, Alloc>::iterator(_array + _size));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const
{
	return (vector<T, Alloc>::const_iterator(_array + _size));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin()
{
	return (vector<T, Alloc>::reverse_iterator(vector<T, Alloc>::iterator(_array + _size)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const
{
	return (vector<T, Alloc>::const_reverse_iterator(vector<T, Alloc>::const_iterator(_array + _size)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend()
{
	return (vector<T, Alloc>::reverse_iterator(vector<T, Alloc>::iterator(_array)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const
{
	return (vector<T, Alloc>::const_reverse_iterator(vector<T, Alloc>::const_iterator(_array)));
}

template <class T, class Alloc>
bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	if (lhs._size != rhs._size)
		return (false);
	for (typename vector<T, Alloc>::size_type i = 0; i < lhs._size; i++)
	{
		if (lhs[i] != rhs[i])
			return (false);
	}
	return (true);
}

template <class T, class Alloc>
bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap (vector<T, Alloc> & x, vector<T, Alloc> & y)
{
	x.swap(y);
}

}

#endif