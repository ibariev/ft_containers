#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "../utils/iterator.hpp"
#include "../utils/red_black_tree.hpp"

namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
class map
{
	public:
		typedef	Key											key_type;
		typedef	T											mapped_type;
		typedef	ft::pair<const key_type, mapped_type>		value_type;
		typedef	Compare										key_compare;
		typedef	Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef	typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef tree_iterator<value_type>					iterator;
		typedef tree_iterator<const value_type>				const_iterator;
		typedef Reverse_iterator<iterator>					reverse_iterator;
		typedef Reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef size_t										size_type;

	private:
		class value_compare
		{ 
  			friend class map;
			protected:
  				Compare comp;
  				value_compare (Compare c) : comp(c) {}
			public:
  				typedef bool result_type;
  				typedef value_type first_argument_type;
  				typedef value_type second_argument_type;
  				bool operator() (const value_type & x, const value_type & y) const
  				{
    				return comp(x.first, y.first);
  				}
		};

		allocator_type	_alloc;
		key_compare		_comp;
		red_black_tree<value_type, value_compare, allocator_type>	_tree;
	
	public:
		explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) :
				_alloc(alloc), _comp(comp), _tree(comp) {}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) :
				_alloc(alloc), _comp(comp), _tree(comp) { _tree.insert(first, last); }
		map (const map & x) : _tree(x._comp) { *this = x; }
		~map() {}

		map & operator= (const map & x)
		{
			if (this == &x)
				return (*this);
			_alloc = x._alloc;
			_comp = x._comp;
			_tree = x._tree;
			return (*this);
		}

		iterator begin() { return (_tree.begin()); }
		const_iterator begin() const { return (_tree.begin()); }
		iterator end() { return (_tree.end()); }
		const_iterator end() const { return (_tree.end()); }
		reverse_iterator rbegin() { return (_tree.rbegin()); }
		const_reverse_iterator rbegin() const { return (_tree.rbegin()); }
		reverse_iterator rend() { return (_tree.rend()); }
		const_reverse_iterator rend() const { return (_tree.rend()); }

		bool empty() const { return (_tree.empty()); }
		size_type size() const { return (_tree.size()); }
		size_type max_size() const { return (_tree.max_size()); }

		mapped_type & operator[] (const key_type & k)
		{ 
			return ((((this->insert(ft::make_pair(k, mapped_type()))).first))->second);
		}

		ft::pair<iterator,bool> insert (const value_type & val) { return (_tree.insert(val)); }
		iterator insert (iterator position, const value_type & val) { return (_tree.insert(position, val)); }
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) { _tree.insert(first, last); }

		void erase (iterator position) { _tree.erase(position); }
		size_type erase (const key_type & k) { return (_tree.erase(ft::make_pair(k, mapped_type()))); }	
		void erase (iterator first, iterator last) { _tree.erase(first, last); }

		void swap (map & x) { _tree.swap(x._tree); }
		void clear() { _tree.clear(); }

		key_compare key_comp() const { return (_comp); }
		value_compare value_comp() const { return (value_compare(key_compare())); }

		iterator find (const key_type & k) { return (_tree.find(ft::make_pair(k, mapped_type()))); }
		const_iterator find (const key_type & k) const { return (_tree.find(ft::make_pair(k, mapped_type()))); }
		size_type count (const key_type & k) const { if (find(k) == end()) return (0); else return (1); }
		iterator lower_bound (const key_type & k) { return (_tree.lower_bound(ft::make_pair(k, mapped_type()))); }
		const_iterator lower_bound (const key_type & k) const { return (_tree.lower_bound(ft::make_pair(k, mapped_type()))); }
		iterator upper_bound (const key_type & k) { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
		const_iterator upper_bound (const key_type & k) const { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
		ft::pair<iterator,iterator> equal_range (const key_type& k) { return (_tree.equal_range(ft::make_pair(k, mapped_type()))); }
		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return (_tree.equal_range(ft::make_pair(k, mapped_type()))); }
		allocator_type get_allocator() const { return (_alloc); }
};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return !(lhs > rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (const map<Key, T, Compare, Alloc> & x, const map<Key, T, Compare, Alloc> & y)
	{
		x.swap(y);
	}

}

#endif