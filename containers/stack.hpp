#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
	private:
		Container _container;
		
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		explicit stack(const container_type & ctnr = container_type());
		bool empty() const;
		size_type size() const;
		value_type & top();
		const value_type & top() const;
		void push(const value_type & val);
		void pop();
		~stack();
	
	private:
		template <class _T, class _Container>
		friend bool operator== (const stack<_T, _Container> & lhs, const stack<_T, _Container> & rhs);

		template <class _T, class _Container>
		friend bool operator< (const stack<_T, _Container> & lhs, const stack<_T, _Container> & rhs);
};

template <class T, class Container>
stack<T, Container>::stack(const stack<T, Container>::container_type & ctnr)
{
	_container = ctnr;
}

template <class T, class Container>
bool stack<T, Container>::empty() const
{
	return (_container.empty());
}

template <class T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const
{
	return (_container.size());
}

template <class T, class Container>
typename stack<T, Container>::value_type & stack<T, Container>::top()
{
	return (_container.back());
}

template <class T, class Container>
const typename stack<T, Container>::value_type & stack<T, Container>::top() const
{
	return (_container.back());
}

template <class T, class Container>
void stack<T, Container>::push(const stack<T, Container>::value_type & val)
{
	_container.push_back(val);
}

template <class T, class Container>
void stack<T, Container>::pop()
{
	_container.pop_back();
}

template <class T, class Container>
stack<T, Container>::~stack()
{

}

template <class T, class Container>
bool operator== (const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs._container == rhs._container);
}

template <class T, class Container>
bool operator!= (const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return !(lhs == rhs);
}

template <class T, class Container>
bool operator< (const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (lhs._container < rhs._container);
}

template <class T, class Container>
bool operator> (const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return (rhs < lhs);
}

template <class T, class Container>
bool operator<= (const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return !(rhs < lhs);
}

template <class T, class Container>
bool operator>= (const stack<T, Container> & lhs, const stack<T, Container> & rhs)
{
	return !(lhs < rhs);
}

}

#endif