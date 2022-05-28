#ifndef TREE_ITERATOR
#define TREE_ITERATOR

#include "node.hpp"

template <class T>
class bidirectional_iterator
{
	public:
		typedef std::ptrdiff_t									difference_type;
		typedef T												value_type;
		typedef T *												pointer;
		typedef T &												reference;
		typedef const T &										const_reference;
		typedef typename std::bidirectional_iterator_tag		iterator_category;

	protected:
		pointer	_ptr;

	public:
		bidirectional_iterator() : _ptr(NULL) {}
		bidirectional_iterator(pointer x) : _ptr(x) {}
		bidirectional_iterator(const bidirectional_iterator<typename ft::remove_const<T>::type> & other) { *this = other; }
		virtual ~bidirectional_iterator() {}
	
		bidirectional_iterator & operator= (const bidirectional_iterator<typename ft::remove_const<T>::type> & other) { _ptr = other.getptr(); return (*this); }
		bool operator== (const bidirectional_iterator & other) { return (_ptr == other._ptr); }
		bool operator!= (const bidirectional_iterator & other) { return (_ptr != other._ptr); }
		const_reference operator* () const { return (*_ptr); }
		pointer operator-> () { return (_ptr); }
		reference operator* () { return (*_ptr); }
		bidirectional_iterator & operator++ () { ++_ptr; return (*this); }
		bidirectional_iterator operator++ (int) { bidirectional_iterator temp(*this); ++(*this); return (temp); }
		bidirectional_iterator & operator-- () { --_ptr; return (*this); }
		bidirectional_iterator operator-- (int) { bidirectional_iterator temp(*this); --(*this); return (temp); }
		pointer getptr() const { return (_ptr); }
};

template <class T>
class tree_iterator : public bidirectional_iterator<node<typename ft::remove_const<T>::type> >
{
	public:
		typedef std::ptrdiff_t									difference_type;
		typedef T												value_type;
		typedef T*												pointer;
		typedef T&												reference;
		typedef const T&										const_reference;
		typedef node<typename ft::remove_const<T>::type> *		node_pointer;
		typedef typename std::bidirectional_iterator_tag		iterator_category;
	
	public:
		tree_iterator() : bidirectional_iterator<node<typename ft::remove_const<T>::type> >(NULL) {}
		tree_iterator(node_pointer x) : bidirectional_iterator<node<typename ft::remove_const<T>::type> >(x) {}
		tree_iterator(const tree_iterator<typename ft::remove_const<T>::type> & other) : bidirectional_iterator<node<typename ft::remove_const<T>::type> >(other) {}
		~tree_iterator() {}

		const tree_iterator & operator= (const tree_iterator<node<typename ft::remove_const<T>::type> > & other) { this->_ptr = other.getptr(); return (*this); }
		bool operator== (const tree_iterator & other) const { return (this->_ptr == other._ptr); }
		bool operator!= (const tree_iterator & other) const { return (this->_ptr != other._ptr); }
		const_reference operator* () const { return *(this->_ptr->_value); }
		pointer operator-> () { return (this->_ptr->_value); }
		reference operator* () { return *(this->_ptr->_value); }
		tree_iterator & operator++ ()
		{
			node_pointer node = this->_ptr;
			if (node->_right)
			{
				node = node->_right;
				while (node->_left)
					node = node->_left;
				this->_ptr = node;
			}
			else if (node->_parent && node->_parent->_left == node)
				this->_ptr = node->_parent;
			else
			{
				while (node->_parent && node == node->_parent->_right)
					node = node->_parent;
				this->_ptr = node->_parent;
			}
			return (*this);
		}
		tree_iterator & operator-- ()
		{
			node_pointer node = this->_ptr;
			if (node->_left)
			{
				node = node->_left;
				while (node->_right)
					node = node->_right;
				this->_ptr = node;
			}
			else if (node->_parent && node->_parent->_right == node)
				this->_ptr = node->_parent;
			else
			{
				while (node->_parent && node == node->_parent->_left)
					node = node->_parent;
				this->_ptr = node->_parent;
			}
			return (*this);
		}
		tree_iterator operator++ (int) { tree_iterator temp = *this; ++(*this); return (temp); }
		tree_iterator operator-- (int) { tree_iterator temp = *this; --(*this); return (temp); }
};

#endif