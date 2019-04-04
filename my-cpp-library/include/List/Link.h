#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:01:40
 * \Description:
 */

#ifndef LINK_H
#define LINK_H

#include "List.h"
#include "LinkNode.h"
#include <ostream>

namespace yxl
{
	template <typename T>
	class Link : public List<T>
	{
	public:
		Link();
		Link(const Link<T>& that);
		Link(Link<T>&& that) noexcept;
		~Link() override = default;

		bool empty() const override;
		int size() const override;
		int index_of(const T& value) const override;
		void clear() override;
		void erase(const int& index) override;
		void insert(const int& index, const T& value) override;

		class Iterator;
		Iterator begin();
		Iterator begin() const;
		Iterator before_begin();
		Iterator before_begin() const;
		Iterator end();
		Iterator end() const;
		void insert(Iterator& index, const T& value);

		T& operator[](const int& index);

		Link& operator=(const Link<T>& right);
		Link& operator=(Link<T>&& right) noexcept;

		template <typename Tt>
		friend std::ostream& operator<<(std::ostream& out, const Link<Tt>& item);
		template <typename Tt>
		friend std::ostream& operator<<(std::ostream& out, Link<Tt>&& item);

	protected:
		int size_{0};
		LinkNode<T>* head_node_;
		LinkNode<T>* rear_node_;

		bool check_index(Iterator& index);
		bool check_index(const int& index) const;
	};

	template <typename T>
	class Link<T>::Iterator
	{
	public:
		using _Mybase = Iterator;
		using iterator_category = std::forward_iterator_tag;

		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T *;
		using const_pointer = const T *;
		using reference = T &;
		using const_reference = const T &;


		Iterator() = default;
		explicit Iterator(LinkNode<T>* that);
		explicit Iterator(const LinkNode<T>* that);
		Iterator(const Iterator& that);
		Iterator(Iterator&& that) noexcept;
		~Iterator() = default;

		bool is_null();

		LinkNode<T>& operator*() const;
		LinkNode<T>* operator->() const;

		Iterator& operator++();
		const Iterator operator++(int);

		Iterator operator+(const int& right) const;

		bool operator!=(const Iterator& right) const;
		bool operator==(const Iterator& right) const;

		Iterator& operator=(const Iterator& right) = default;
		Iterator& operator=(Iterator&& right) noexcept = default;

	private:
		LinkNode<T>* position_;
	};

	class Node;

	template <typename T>
	Link<T>::Link()
	{
		head_node_ = new LinkNode<T>();
		rear_node_ = new LinkNode<T>();
		rear_node_->next = head_node_;
		head_node_->next = rear_node_;
	}

	template <typename T>
	Link<T>::Link(const Link<T>& that)
	{
		size_ = that.size_;
		head_node_ = new LinkNode<T>(that.head_node_->value);
		rear_node_ = new LinkNode<T>(that.rear_node_->value);
		rear_node_->next = head_node_;
		head_node_->next = rear_node_;
		LinkNode<T>* this_node = head_node_;
		LinkNode<T>* that_node = that.head_node_;
		for (auto i = 0; i < size_; ++i)
		{
			that_node = that_node->next;
			this_node->next = new LinkNode<T>(that_node->value, this_node->next);
			this_node = this_node->next;
		}
	}

	template <typename T>
	Link<T>::Link(Link<T>&& that) noexcept
	{
		size_ = that.size_;
		head_node_ = that.head_node_;
		rear_node_ = that.rear_node_;
		that.size_ = 0;
		that.head_node_ = nullptr;
		that.rear_node_ = nullptr;
	}

	template <typename T>
	bool Link<T>::empty() const
	{
		return size_ == 0;
	}

	template <typename T>
	int Link<T>::size() const
	{
		return size_;
	}

	template <typename T>
	int Link<T>::index_of(const T& value) const
	{
		auto index = 0;
		LinkNode<T>* current_node = head_node_->next;
		while (current_node != rear_node_ && current_node->value != value)
		{
			current_node = current_node->next;
			++index;
		}
		if (current_node == rear_node_) { return -1; }
		return index;
	}

	template <typename T>
	void Link<T>::clear()
	{
		LinkNode<T>* previous_node = head_node_;
		LinkNode<T>* current_node = head_node_->next;
		for (auto i = 0; i < size_; ++i)
		{
			delete previous_node;
			previous_node = current_node;
			current_node = current_node->next;
		}
		delete previous_node;
		delete current_node;
		size_ = 0;
		head_node_ = new LinkNode<T>();
		rear_node_ = new LinkNode<T>();
		rear_node_->next = head_node_;
		head_node_->next = rear_node_;
	}

	template <typename T>
	void Link<T>::erase(const int& index)
	{
		if (check_index(index))
		{
			LinkNode<T>* current_node;
			if (index == 0) { current_node = head_node_; }
			else { current_node = head_node_->next; }
			for (auto i = 1; i < index; ++i)
			{
				current_node = current_node->next;
			}
			LinkNode<T>* erase_node = current_node->next;
			current_node->next = current_node->next->next;
			delete erase_node;
			--size_;
		}
	}

	template <typename T>
	void Link<T>::insert(const int& index, const T& value)
	{
		if (check_index(index) || index == size_)
		{
			LinkNode<T>* current_node = head_node_;
			for (auto i = 0; i < index; ++i)
			{
				current_node = current_node->next;
			}
			current_node->next = new LinkNode<T>(value, current_node->next);
			++size_;
		}
	}

	template <typename T>
	typename Link<T>::Iterator Link<T>::begin()
	{
		return Iterator(head_node_->next);
	}

	template <typename T>
	typename Link<T>::Iterator Link<T>::begin() const
	{
		return Iterator(head_node_->next);
	}

	template <typename T>
	typename Link<T>::Iterator Link<T>::before_begin()
	{
		return Iterator(head_node_);
	}

	template <typename T>
	typename Link<T>::Iterator Link<T>::before_begin() const
	{
		return Iterator(head_node_);
	}

	template <typename T>
	typename Link<T>::Iterator Link<T>::end()
	{
		return Iterator(rear_node_);
	}

	template <typename T>
	typename Link<T>::Iterator Link<T>::end() const
	{
		return Iterator(rear_node_);
	}

	template <typename T>
	void Link<T>::insert(Iterator& index, const T& value)
	{
		if (check_index(index))
		{
			index->next = new LinkNode<T>(value, index->next);
			++size_;
		}
	}

	template <typename T>
	T& Link<T>::operator[](const int& index)
	{
		if (check_index(index))
		{
			LinkNode<T>* current_node = head_node_->next;
			for (auto i = 0; i < index; ++i)
			{
				current_node = current_node->next;
			}
			return current_node->value;
		}
		return head_node_->value;
	}

	template <typename T>
	Link<T>& Link<T>::operator=(const Link<T>& right)
	{
		size_ = right.size_;
		head_node_ = new LinkNode<T>(right.head_node_->value);
		rear_node_ = new LinkNode<T>(right.rear_node_->value);
		rear_node_->next = head_node_;
		head_node_->next = rear_node_;
		LinkNode<T>* this_node = head_node_;
		LinkNode<T>* that_node = right.head_node_;
		for (auto i = 0; i < size_; ++i)
		{
			that_node = that_node->next;
			this_node->next = new LinkNode<T>(that_node->value, this_node->next);
			this_node = this_node->next;
		}
		return *this;
	}

	template <typename T>
	Link<T>& Link<T>::operator=(Link<T>&& right) noexcept
	{
		size_ = right.size_;
		head_node_ = right.head_node_;
		rear_node_ = right.rear_node_;
		right.size_ = 0;
		right.head_node_ = nullptr;
		right.rear_node_ = nullptr;
		return *this;
	}

	template <typename T>
	bool Link<T>::check_index(Iterator& index)
	{
		return !index.is_null() && index != end();
	}

	template <typename T>
	bool Link<T>::check_index(const int& index) const
	{
		return index >= 0 && index < size_;
	}

	template <typename T>
	Link<T>::Iterator::Iterator(LinkNode<T>* that)
	{
		position_ = that;
	}

	template <typename T>
	Link<T>::Iterator::Iterator(const LinkNode<T>* that)
	{
		position_ = that;
	}

	template <typename T>
	Link<T>::Iterator::Iterator(const Iterator& that)
	{
		position_ = that.position_;
	}

	template <typename T>
	Link<T>::Iterator::Iterator(Iterator&& that) noexcept
	{
		position_ = that.position_;
		that.position_ = nullptr;
	}

	template <typename T>
	bool Link<T>::Iterator::is_null()
	{
		return position_ == nullptr;
	}

	template <typename T>
	LinkNode<T>& Link<T>::Iterator::operator*() const
	{
		return *position_;
	}

	template <typename T>
	LinkNode<T>* Link<T>::Iterator::operator->() const
	{
		return &*position_;
	}

	template <typename T>
	typename Link<T>::Iterator& Link<T>::Iterator::operator++()
	{
		position_ = position_->next;
		return *this;
	}

	template <typename T>
	const typename Link<T>::Iterator Link<T>::Iterator::operator++(int)
	{
		Iterator old = *this;
		position_ = position_->next;
		return old;
	}

	template <typename T>
	typename Link<T>::Iterator Link<T>::Iterator::operator+(const int& right) const
	{
		Iterator old = *this;
		for (auto i = 0; i < right; ++i)
		{
			old.position_ = old.position_->next;
		}
		return old;
	}

	template <typename T>
	bool Link<T>::Iterator::operator!=(const Iterator& right) const
	{
		return position_ != right.position_;
	}

	template <typename T>
	bool Link<T>::Iterator::operator==(const Iterator& right) const
	{
		return position_ == right.position_;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const Link<T>& item)
	{
        for (auto& i : item)
        {
            out << i << ' ';
        }
		out << std::endl;
        return out;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, Link<T>&& item)
	{
        for (auto& i : item)
        {
            out << i << ' ';
        }
		out << std::endl;
        return out;
	}
} // namespace yxl

#endif // !LINK_H
