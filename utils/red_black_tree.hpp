#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>
#include "node.hpp"
#include "iterator.hpp"
#include "tree_iterator.hpp"

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class red_black_tree
{
	public:
		typedef T													value_type;
		typedef	Alloc												allocator_type;
		typedef	Compare												compare;
		typedef typename Alloc::template rebind<node<T> >::other	node_alloc;
		typedef typename node_alloc::pointer						node_pointer;
		typedef tree_iterator<value_type>							iterator;
		typedef tree_iterator<const value_type>						const_iterator;
		typedef ft::Reverse_iterator<iterator>						reverse_iterator;
		typedef ft::Reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef size_t												size_type;

	private:
		node_pointer	_start;
		node_pointer	_end;
		node_pointer	_root;
		size_type		_size;
		compare			_compare;
		node_alloc		_node_alloc;

	public:
		red_black_tree(const compare & comp) : _size(0), _compare(comp), _node_alloc(node_alloc())
		{
			_start = _node_alloc.allocate(1);
			_node_alloc.construct(_start, node<value_type>());
			_end = _start;
			_root = _start;
		}
		red_black_tree(const red_black_tree & other) { *this = other; }
		red_black_tree & operator= (const red_black_tree & other)
		{
			if (this == &other)
				return (*this);
			_size = other._size;
			_compare = other._compare;
			_node_alloc = other._node_alloc;
			if (other.empty())
			{
				_start = _end;
				_root = _end;
			}
			else
			{
				_root = deep_node_copy(other._root);
				set_end();
				_start = min(_root);
			}
			return (*this);
		}
		~red_black_tree() 
		{
			remove_node(_root);
		}

		iterator begin() { return (this->empty() ? iterator(_end) : iterator(_start)); }
		const_iterator begin() const { return (this->empty() ? const_iterator(_end) : const_iterator(_start)); }
		iterator end() { return (iterator(_end)); }
		const_iterator end() const { return (const_iterator(_end)); }
		reverse_iterator rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

		bool empty() const
		{
			return (_root == NULL || (_root->_left == NULL && _root->_right == NULL && _root->_value == NULL));
		}
		size_type size() const
		{
			return (_size);
		}
		size_type max_size() const
		{
			return (_node_alloc.max_size());
		}

		ft::pair<iterator, bool> insert(const value_type & val)
		{
			node_pointer current = _root;
			node_pointer parent = NULL;
			node_pointer new_node = _node_alloc.allocate(1);

			_node_alloc.construct(new_node, node<value_type>(val, RED));
			while (current != NULL)
			{
				if (current->_left == NULL && current->_right == NULL && current->_value == NULL)
					break ;
				parent = current;
				if (_compare(*(new_node->_value), *(current->_value)))
					current = current->_left;
				else if (_compare(*(current->_value), *(new_node->_value)))
					current = current->_right;
				else
				{
					remove_node(new_node);
					return (ft::make_pair(iterator(current), false));
				}
			}
			new_node->_parent = parent;
			if (parent == NULL)
				_root = new_node;
			else if (_compare(*(new_node->_value), *(parent->_value)))
				parent->_left = new_node;
			else
				parent->_right = new_node;
			insert_fixup(new_node);
			_size += 1;
			set_end();
			_start = min(_root);
			return (ft::make_pair(iterator(new_node), true));
		}

		iterator insert(iterator position, const value_type & val)
		{
			node_pointer nod = search(val, _root);
			if (nod)
				return (iterator(nod));
			node_pointer current = position.getptr();
			node_pointer parent = NULL;
			if (current)
				parent = current->_parent;
			if (parent && _compare(*(parent->_value), val))
				return (insert(parent, val));
			node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, node<value_type>(val, RED));
			while (current != NULL)
			{
				if (current->_left == NULL && current->_right == NULL && current->_value == NULL)
					break ;
				parent = current;
				if (_compare(*(new_node->_value), *(current->_value)))
					current = current->_left;
				else if (_compare(*(current->_value), *(new_node->_value)))
					current = current->_right;
				else 
				{
					remove_node(new_node);
					return (iterator(current));
				}
			}
			new_node->_parent = parent;
			if (parent == NULL)
				_root = new_node;
			else if (_compare(*(new_node->_value), *(parent->_value)))
				parent->_left = new_node;
			else
				parent->_right = new_node;
			insert_fixup(new_node);
			_size += 1;
			set_end();
			_start = min(_root);
			return (iterator(new_node));
		}
		
		template <class InputIterator>
  		void insert (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase (iterator position)
		{
			delete_node(*position);
			_start = min(_root);
		}

		size_type erase (const value_type & k)
		{
			size_type prev = _size;
			
			delete_node(k);
			_start = min(_root);
			if (_size == prev)
				return (0);
			return (1);
		}

		void erase (iterator first, iterator last)
		{
			while (first != last)
				erase(*first++);
		}

		void swap (red_black_tree & x)
		{
			std::swap(_size, x._size);
			std::swap(_root, x._root);
			std::swap(_start, x._start);
			std::swap(_end, x._end);
		}

		void clear()
		{
			remove_node(_root);
		}

		iterator find (const value_type & k)
		{
			node_pointer res = search(k, _root);
			if (res)
				return (iterator(res));
			return (end());
		}

		const_iterator find (const value_type & k) const
		{
			node_pointer res = search(k, _root);
			if (res)
				return (const_iterator(res));
			return (end());
		}

		iterator lower_bound (const value_type & k)
		{
			iterator first = begin();
			iterator last = end();

			while (first != last)
			{
				if (_compare(*first, k) == false)
					return (first);
				first++;
			}
			return (last);
		}

		const_iterator lower_bound (const value_type & k) const
		{
			const_iterator first = begin();
			const_iterator last = end();

			while (first != last)
			{
				if (_compare(*first, k) == false)
					return (first);
				first++;
			}
			return (last);
		}

		iterator upper_bound (const value_type & k)
		{
			iterator first = begin();
			iterator last = end();

			while (first != last)
			{
				if (_compare(k, *first))
					return (first);
				first++;
			}
			return (last);
		}

		const_iterator upper_bound (const value_type & k) const
		{
			const_iterator first = begin();
			const_iterator last = end();

			while (first != last)
			{
				if (_compare(k, *first))
					return (first);
				first++;
			}
			return (last);
		}

		ft::pair<iterator, iterator> equal_range (const value_type & k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}	

		ft::pair<const_iterator, const_iterator> equal_range (const value_type & k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		void delete_node(const value_type & val)
		{
			node_pointer node = search(val, _root);
			node_pointer child = NULL;
			bool node_color;

			if (node == NULL)
				return ;
			if (node->_left == NULL || node->_right == NULL) 
			{
				child = get_new_child(node);
				node_color = node->_color;
				delete_node_value(node);
				_node_alloc.deallocate(node, 1);
			}
			else 
			{
				node_pointer next = min(node->_right);
				value_type * val = next->_value;

				child = get_new_child(next);
				node_color = next->_color;
				delete_node_value(node);
				node->_value = val;
				_node_alloc.deallocate(next, 1);
			}
			if (node_color == BLACK && _root != _end)
			{
				delete_fixup(child);
				if (child->_value == NULL)
				{
					swap_parents(child->_parent, child, NULL);
					_node_alloc.deallocate(child, 1);
				}
			}
			_size -= 1;
		}
		
		void delete_fixup(node_pointer node) 
		{
			if (node == _root) // case 1
			{
				node->_color = BLACK;
				return ;
			}
			node_pointer sibling = get_sibling(node);
			if (sibling->_color == RED) // case 2
			{
				handle_red_sibling(node, sibling);
				sibling = get_sibling(node);
			}
			if (is_black(sibling->_left) && is_black(sibling->_right))
			{
				sibling->_color = RED;
				if (node->_parent->_color == RED) // case 4
					node->_parent->_color = BLACK;
				else
					delete_fixup(node->_parent); // case 3
			}
			else
			{
				bool node_is_left = (node == node->_parent->_left) ? true : false;
				if (!node_is_left && is_black(sibling->_left)) // case 5
				{
					sibling->_right->_color = BLACK;
					sibling->_color = RED;
					left_rotate(sibling);
					sibling = node->_parent->_left;
				}
				else if (node_is_left && is_black(sibling->_right))
				{
					sibling->_left->_color = BLACK;
					sibling->_color = RED;
					right_rotate(sibling);
					sibling = node->_parent->_right;
				}
				sibling->_color = node->_parent->_color; // case 6
				node->_parent->_color = BLACK;
				if (node_is_left)
				{
					sibling->_right->_color = BLACK;
					left_rotate(node->_parent);
				} 
				else
				{
					sibling->_left->_color = BLACK;
					right_rotate(node->_parent);
				}
			}
		}
		
		node_pointer get_sibling(node_pointer node)
		{
			node_pointer parent = node->_parent;

			if (node == parent->_left)
				return (parent->_right);
			else if (node == parent->_right)
				return (parent->_left);
			return (NULL);
		}
		
		void handle_red_sibling(node_pointer node, node_pointer sibling)
		{
			node->_parent->_color = RED;
			sibling->_color = BLACK;
			if (node == node->_parent->_left)
				left_rotate(node->_parent);
		 	else
				right_rotate(node->_parent);
		}

		bool is_black(node_pointer node)
		{
			if (node == NULL || node->_color == BLACK)
				return (true);
			return (false);
		}
		node_pointer get_new_child(node_pointer nod)
		{
			if (nod->_left)
			{
				swap_parents(nod->_parent, nod, nod->_left);
				return (nod->_left);
			} 
			else if (nod->_right)
			{
				swap_parents(nod->_parent, nod, nod->_right);
				return (nod->_right);
			}
			else
			{
				node_pointer new_child;
				if (nod->_color == BLACK)
				{
					new_child = _node_alloc.allocate(1);
					_node_alloc.construct(new_child, node<value_type>());
				}
				else
					new_child = NULL;
				swap_parents(nod->_parent, nod, new_child);
				return (new_child);
			}
			return (NULL);
		}

		void delete_node_value(node_pointer node) 
		{
			node->_alloc.destroy(node->_value);
			node->_alloc.deallocate(node->_value, 1);
		}

		node_pointer search(const value_type & value, node_pointer node) const
		{
			if (node == NULL || node->_value == NULL)
				return (NULL);
			if (_compare(value, *(node->_value)))
				return (search(value, node->_left));
			if (_compare(*(node->_value), value))
				return (search(value, node->_right));
			return (node);
		}

		void insert_fixup(node_pointer node)
		{
			node_pointer parent = node->_parent;
			if (parent == NULL) // case 1
			{
				node->_color = BLACK;
				return ;
			}
			if (parent->_color == BLACK) // case 2
				return ;
			node_pointer grandfather = parent->_parent;
			node_pointer uncle = get_uncle(parent);
			if (uncle && uncle->_color == RED) // case 3
			{
				uncle->_color = BLACK;
				parent->_color = BLACK;
				grandfather->_color = RED;
				insert_fixup(grandfather);
			}
			else if (parent == grandfather->_left)
			{
				if (node == parent->_right) // case 4 left
				{
					left_rotate(parent);
					parent = node;
				}
				right_rotate(grandfather); // case 5 left
				grandfather->_color = RED;
				parent->_color = BLACK;
			}
			else
			{
				if (node == parent->_left) // case 4 right
				{
					right_rotate(parent);
					parent = node;
				}
				left_rotate(grandfather); // case 5 right
				grandfather->_color = RED;
				parent->_color = BLACK;
			}
		}

		node_pointer get_uncle(node_pointer node)
		{
			node_pointer parent = node->_parent;
			if (parent && parent->_left == node)
				return (parent->_right);
			else if (parent && parent->_right == node)
				return (parent->_left);
			return (NULL);
		}

		void left_rotate(node_pointer parent)
		{
			node_pointer grandfather = parent->_parent;
			node_pointer child = parent->_right;

			parent->_right = child->_left;
			if (child->_left)
				child->_left->_parent = parent;
			child->_left = parent;
			parent->_parent = child;
			swap_parents(grandfather, parent, child);
		}

		void right_rotate(node_pointer parent)
		{
			node_pointer grandfather = parent->_parent;
			node_pointer child = parent->_left;

			parent->_left = child->_right;
			if (child->_right)
				child->_right->_parent = parent;
			child->_right = parent;
			parent->_parent = child;
			swap_parents(grandfather, parent, child);
		}

		void swap_parents(node_pointer grandfather, node_pointer parent, node_pointer child)
		{
			if (grandfather == NULL)
				_root = child;
			else if (grandfather->_left == parent)
				grandfather->_left = child;
			else if (grandfather->_right == parent)
				grandfather->_right = child;
			if (child)
				child->_parent = grandfather;
		}

		node_pointer deep_node_copy(node_pointer other)
		{
			if (other == NULL || (other->_left == NULL && other->_right == NULL && other->_value == NULL))
				return (NULL);
			node_pointer new_node = clone_node(other);
			new_node->_left = deep_node_copy(other->_left);
			if (new_node->_left)
				new_node->_left->_parent = new_node;
			new_node->_right = deep_node_copy(other->_right);
			if (new_node->_right)
				new_node->_right->_parent = new_node;
			return (new_node);
		}

		node_pointer clone_node(node_pointer other) 
		{
			if (other)
			{
				node_pointer new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, node<value_type>(*other));
				return (new_node);
			}
			return (NULL);
		}

		void set_end(void)
		{
			node_pointer max = this->max(_root);
			if (this->empty())
			{
				_end = max;
				return ;
			}
			max->_right = _end;
			_end->_parent = max;
		}

		node_pointer max(node_pointer node)
		{
			if (node == NULL)
				return (NULL);
			while (node->_right && node->_right->_value)
				node = node->_right;
			return (node);
		}

		node_pointer min(node_pointer node) const
		{
			if (node == NULL)
				return (NULL);
			while (node->_left) //&& node->_left->_value)
				node = node->_left;
			return (node);
		}

		void remove_node(node_pointer node) 
		{
			if (node == NULL)
				return ;
			remove_node(node->_left);
			remove_node(node->_right);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}
};


#endif