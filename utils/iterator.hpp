#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include "utils.hpp"

namespace ft
{

template <class Iterator>
class iterator_traits
{
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
class iterator_traits<T*>
{
	public:
		typedef std::ptrdiff_t								difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
	public:
		typedef std::ptrdiff_t								difference_type;
		typedef const T										value_type;
		typedef const T*									pointer;
		typedef const T&									reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
};

template <class T>
class random_access_iterator
{
	public:
		typedef std::ptrdiff_t									difference_type;
		typedef T												value_type;
		typedef T*												pointer;
		typedef T&												reference;
		typedef const T&										const_reference;
		typedef typename std::random_access_iterator_tag		iterator_category;
	
	private:
		pointer	_ptr;
	
	public:
		random_access_iterator() { _ptr = NULL; }
		random_access_iterator(pointer x) { _ptr = x; }
		random_access_iterator(const random_access_iterator<typename ft::remove_const<T>::type> & other) { *this = other; }
		~random_access_iterator() {}

		const random_access_iterator & operator= (const random_access_iterator<typename ft::remove_const<T>::type> & other) { _ptr = other.getptr(); return (*this); }
		bool operator== (const random_access_iterator & other) const { return (_ptr == other._ptr); }
		bool operator!= (const random_access_iterator & other) const { return (_ptr != other._ptr); }
		const_reference operator* () const { return (*_ptr); }
		pointer operator-> () { return (_ptr); }
		reference operator* () { return (*_ptr); }
		random_access_iterator & operator++ () { ++_ptr; return (*this); }
		random_access_iterator operator++ (int) { random_access_iterator temp = *this; _ptr++; return (temp); }
		random_access_iterator & operator-- () { --_ptr; return (*this); }
		random_access_iterator operator-- (int) { random_access_iterator temp = *this; _ptr--; return (temp); }
		random_access_iterator operator+ (difference_type n) const { random_access_iterator res(_ptr + n); return (res); }
		friend random_access_iterator operator+ (difference_type n, const random_access_iterator & it) { random_access_iterator res(it._ptr + n); return (res); }
		random_access_iterator operator- (difference_type n) const { random_access_iterator res(_ptr - n); return (res); }
		difference_type operator- (const random_access_iterator & it) const { return (_ptr - it._ptr); }
		template <class A, class B>
		friend bool operator< (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs);
		template <class A, class B>
		friend bool operator> (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs);
		template <class A, class B>
		friend bool operator<= (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs);
		template <class A, class B>
		friend bool operator>= (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs);
		random_access_iterator & operator+= (difference_type n) { _ptr += n; return (*this); }
		random_access_iterator & operator-= (difference_type n) { _ptr -= n; return (*this); }
		reference operator[] (difference_type n) { return *(_ptr + n); }
		pointer getptr() const { return (_ptr); }
};

template <class A, class B>
bool operator< (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return (lhs._ptr < rhs._ptr);
}

template <class A, class B>
bool operator> (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return (lhs._ptr > rhs._ptr);
}

template <class A, class B>
bool operator<= (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return (lhs._ptr <= rhs._ptr);
}

template <class A, class B>
bool operator>= (const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return (lhs._ptr >= rhs._ptr);
}

template <class Iterator>
class Reverse_iterator
{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
	
	private:
		iterator_type _base;
	
	public:
		Reverse_iterator() : _base() {}
		explicit Reverse_iterator(iterator_type it) : _base(it) {}
		template <class Iter>
		Reverse_iterator (const Reverse_iterator<Iter> & rev_it) : _base(rev_it.base()) {}
		~Reverse_iterator() {}

		iterator_type base() const { return (_base); }
		reference operator* () const { iterator_type copy(_base); return *(--copy); }
		Reverse_iterator operator+ (difference_type n) const { Reverse_iterator res(_base - n); return (res); }
		Reverse_iterator & operator++ () { --_base; return (*this); }
		Reverse_iterator operator++ (int) { Reverse_iterator temp(*this); ++(*this); return (temp); }
		Reverse_iterator & operator+= (difference_type n) { _base -= n; return (*this); }
		Reverse_iterator operator- (difference_type n) const { Reverse_iterator res(_base + n); return (res); }
		Reverse_iterator & operator-- () { ++_base; return (*this); }
		Reverse_iterator operator-- (int) { Reverse_iterator temp(*this); --(*this); return (temp); }
		Reverse_iterator & operator-= (difference_type n) { _base += n; return (*this); }
		pointer operator-> () const { return &(operator*()); }
		reference operator[] (difference_type n) const { return (base()[-n - 1]); }
		template <class _Iterator>
		friend bool operator== (const Reverse_iterator<_Iterator> & lhs, const Reverse_iterator<_Iterator> & rhs);
		template <class _Iterator>
		friend bool operator!= (const Reverse_iterator<_Iterator> & lhs, const Reverse_iterator<_Iterator> & rhs);
		template <class _Iterator>
		friend bool operator< (const Reverse_iterator<_Iterator> & lhs, const Reverse_iterator<_Iterator> & rhs);
		template <class _Iterator>
		friend bool operator<= (const Reverse_iterator<_Iterator> & lhs, const Reverse_iterator<_Iterator> & rhs);
		template <class _Iterator>
		friend bool operator> (const Reverse_iterator<_Iterator> & lhs, const Reverse_iterator<_Iterator> & rhs);
		template <class _Iterator>
		friend bool operator>= (const Reverse_iterator<_Iterator> & lhs, const Reverse_iterator<_Iterator> & rhs);
		template <class _Iterator>
  		friend Reverse_iterator<_Iterator> operator+ (typename Reverse_iterator<_Iterator>::difference_type n, const Reverse_iterator<_Iterator>& rev_it);
		template <class _Iterator>
  		friend typename Reverse_iterator<_Iterator>::difference_type operator- (const Reverse_iterator<_Iterator>& lhs, const Reverse_iterator<_Iterator>& rhs);
};

template <class Iterator>
bool operator== (const Reverse_iterator<Iterator> & lhs, const Reverse_iterator<Iterator> & rhs)
{
	return (lhs._base == rhs._base);
}

template <class Iterator>
bool operator!= (const Reverse_iterator<Iterator> & lhs, const Reverse_iterator<Iterator> & rhs)
{
	return (lhs._base != rhs._base);
}

template <class Iterator>
bool operator< (const Reverse_iterator<Iterator> & lhs, const Reverse_iterator<Iterator> & rhs)
{
	return (lhs._base > rhs._base);
}

template <class Iterator>
bool operator<= (const Reverse_iterator<Iterator> & lhs, const Reverse_iterator<Iterator> & rhs)
{
	return (lhs._base >= rhs._base);
}

template <class Iterator>
bool operator> (const Reverse_iterator<Iterator> & lhs, const Reverse_iterator<Iterator> & rhs)
{
	return (lhs._base < rhs._base);
}

template <class Iterator>
bool operator>= (const Reverse_iterator<Iterator> & lhs, const Reverse_iterator<Iterator> & rhs)
{
	return (lhs._base <= rhs._base);
}

template <class Iterator>
Reverse_iterator<Iterator> operator+ (typename Reverse_iterator<Iterator>::difference_type n, const Reverse_iterator<Iterator>& rev_it)
{
	Reverse_iterator<Iterator> res(rev_it._base - n);
	return (res);
}

template <class Iterator>
typename Reverse_iterator<Iterator>::difference_type operator- (const Reverse_iterator<Iterator>& lhs, const Reverse_iterator<Iterator>& rhs)
{
	return (rhs._base - lhs._base);
}

}

#endif