#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"
#include <iostream>
#define BLACK 1
#define RED 0

template <class T>
struct node
{
	typedef	std::allocator<T>					allocator_type;
	typedef	typename allocator_type::pointer	pointer;
	
	allocator_type		_alloc;
	pointer				_value;
	node<T> *			_parent;
	node<T> *			_left;
	node<T> *			_right;
	bool				_color;
	
	node() : _alloc(allocator_type()), _value(NULL), _parent(NULL), _left(NULL), _right(NULL), _color(BLACK) {}
	node(const T & value, bool color = BLACK) : _alloc(allocator_type()), _parent(NULL), _left(NULL), _right(NULL), _color(color)
	{
		_value = _alloc.allocate(1);
		_alloc.construct(_value, value);
	}
	node(const node & other) { *this = other; }
	node & operator=(const node & other)
	{
		if (this == &other)
			return (*this);
		if (other._value)
		{
			_value = _alloc.allocate(1);
			_alloc.construct(_value, *(other._value));
		}
		else
			_value = other._value;
		_alloc = other._alloc;
		_parent = other._parent;
		_left = other._left;
		_right = other._right;
		_color = other._color;
		return (*this);
	}
	~node()
	{
		if (_value)
		{
			_alloc.destroy(_value);
			_alloc.deallocate(_value, 1);
		}
	}
};

#endif