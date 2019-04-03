#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:24:20
 * \Description:
 */

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "Stack.h"

namespace yxl
{
	template <typename T>
	class ArrayStack final : public Stack<T>
	{
	public:
		ArrayStack();
		ArrayStack(const ArrayStack<T>& that);
		ArrayStack(ArrayStack<T>&& that) noexcept;
		~ArrayStack() override = default;

		bool empty() const override;
		int size() const override;
		T& top() const override;
		void clear() override;
		void pop() override;
		void push(const T& value) override;

		ArrayStack& operator=(const ArrayStack<T>& right);
		ArrayStack& operator=(ArrayStack<T>&& right) noexcept;

	private:
		T* array_;
		int top_{-1};
		int size_;

		void change_size();
	};

	template <typename T>
	ArrayStack<T>::ArrayStack(): size_(1 << 10)
	{
		array_ = new T[size_];
	}

	template <typename T>
	ArrayStack<T>::ArrayStack(const ArrayStack<T>& that)
	{
		size_ = that.size_;
		top_ = that.top_;
		array_ = new T[size_];
		for (auto i = 0; i < size_; ++i)
		{
			array_[i] = that.array_[i];
		}
	}

	template <typename T>
	ArrayStack<T>::ArrayStack(ArrayStack<T>&& that) noexcept
	{
		top_ = that.top_;
		size_ = that.size_;
		array_ = that.array_;
		that.top_ = 0;
		that.size_ = 0;
		that.array_ = nullptr;
	}

	template <typename T>
	bool ArrayStack<T>::empty() const
	{
		return top_ == -1;
	}

	template <typename T>
	int ArrayStack<T>::size() const
	{
		return top_ + 1;
	}

	template <typename T>
	T& ArrayStack<T>::top() const
	{
		if (top_ >= 0) { return array_[top_]; }
		return array_[0];
	}

	template <typename T>
	void ArrayStack<T>::clear()
	{
		delete[] array_;
		top_ = 0;
		size_ = 1 << 10;
		array_ = new T[size_];
	}

	template <typename T>
	void ArrayStack<T>::pop()
	{
		if (top_ >= 0) { --top_; }
	}

	template <typename T>
	void ArrayStack<T>::push(const T& value)
	{
		if (top_ == size_ - 1) { change_size(); }
		array_[++top_] = value;
	}

	template <typename T>
	ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& right)
	{
		size_ = right.size_;
		top_ = right.top_;
		array_ = new T[size_];
		for (auto i = 0; i < size_; ++i)
		{
			array_[i] = right.array_[i];
		}
		return *this;
	}

	template <typename T>
	ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack<T>&& right) noexcept
	{
		top_ = right.top_;
		size_ = right.size_;
		array_ = right.array_;
		right.top_ = 0;
		right.size_ = 0;
		right.array_ = nullptr;
		return *this;
	}

	template <typename T>
	void ArrayStack<T>::change_size()
	{
		T* temp = new T[size_ * 2];
		for (auto i = 0; i < size_; ++i)
		{
			temp[i] = array_[i];
		}
		delete[] array_;
		size_ <<= 1;
		array_ = temp;
	}
} // namespace yxl

#endif // !ARRAY_STACK_H
