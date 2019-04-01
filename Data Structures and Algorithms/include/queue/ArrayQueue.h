/**
 * \Author: YXL
 * \LastUpdated: 2018/03/15 14:19:10
 * \Description:
 */

#pragma once

#ifndef YXL_ARRAY_QUEUE_H
#define YXL_ARRAY_QUEUE_H

#include "Queue.h"

namespace yxl
{
	template <typename T>
	class ArrayQueue final : public Queue<T>
	{
	public:
		ArrayQueue();
		ArrayQueue(ArrayQueue<T>& that);
		ArrayQueue(ArrayQueue<T>&& that) noexcept;
		~ArrayQueue() override = default;

		bool empty() const override;
		int size() const override;
		T& front() const override;
		T& back() const override;
		void clear() override;
		void pop() override;
		void push_front(const T& value) override;
		void push_back(const T& value) override;

		ArrayQueue& operator=(const ArrayQueue<T>& right);
		ArrayQueue& operator=(ArrayQueue<T>&& right) noexcept;

	private:
		T* array_;
		int front_;
		int back_;
		int size_;

		void change_size();
	};

	template <typename T>
	ArrayQueue<T>::ArrayQueue(): front_(0), back_(0), size_(1 << 10)
	{
		array_ = new T[size_];
	}

	template <typename T>
	ArrayQueue<T>::ArrayQueue(ArrayQueue<T>& that)
	{
		size_ = that.size_;
		front_ = that.front_;
		back_ = that.back_;
		array_ = new T[size_];
		for (auto i = 0; i < size_; ++i)
		{
			array_[i] = that.array_[i];
		}
	}

	template <typename T>
	ArrayQueue<T>::ArrayQueue(ArrayQueue<T>&& that) noexcept
	{
		size_ = that.size_;
		front_ = that.front_;
		back_ = that.back_;
		array_ = that.array_;
		that.size_ = 0;
		that.front_ = 0;
		that.back_ = 0;
		that.array_ = nullptr;
	}

	template <typename T>
	bool ArrayQueue<T>::empty() const
	{
		return front_ == back_;
	}

	template <typename T>
	int ArrayQueue<T>::size() const
	{
		return (back_ - front_ + size_) % size_;
	}

	template <typename T>
	T& ArrayQueue<T>::front() const
	{
		return array_[(front_ + 1) % size_];
	}

	template <typename T>
	T& ArrayQueue<T>::back() const
	{
		return array_[back_];
	}

	template <typename T>
	void ArrayQueue<T>::clear()
	{
		delete[] array_;
		front_ = 0;
		back_ = 0;
		size_ = 1 << 10;
		array_ = new T[size_];
	}

	template <typename T>
	void ArrayQueue<T>::pop()
	{
		if (front_ != back_) { front_ = (front_ + 1) % size_; }
	}

	template <typename T>
	void ArrayQueue<T>::push_front(const T& value)
	{
		if ((back_ + 1) % size_ == front_) { change_size(); }
		array_[front_] = value;
		front_ = (front_ + size_ - 1) % size_;
	}

	template <typename T>
	void ArrayQueue<T>::push_back(const T& value)
	{
		if ((back_ + 1) % size_ == front_) { change_size(); }
		back_ = (back_ + 1) % size_;
		array_[back_] = value;
	}

	template <typename T>
	ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& right)
	{
		size_ = right.size_;
		front_ = right.front_;
		back_ = right.back_;
		array_ = new T[size_];
		for (auto i = 0; i < size_; ++i)
		{
			array_[i] = right.array_[i];
		}
		return *this;
	}

	template <typename T>
	ArrayQueue<T>& ArrayQueue<T>::operator=(ArrayQueue<T>&& right) noexcept
	{
		size_ = right.size_;
		front_ = right.front_;
		back_ = right.back_;
		array_ = right.array_;
		right.size_ = 0;
		right.front_ = 0;
		right.back_ = 0;
		right.array_ = nullptr;
		return *this;
	}

	template <typename T>
	void ArrayQueue<T>::change_size()
	{
		auto index = 0;
		T* temp = new T[size_ * 2];
		while (front_ != back_ && index < size_ * 2 - 1)
		{
			front_ = (front_ + 1) % size_;
			temp[++index] = array_[front_];
		}
		delete[] array_;
		size_ <<= 1;
		array_ = temp;
		front_ = 0;
		back_ = index;
	}
}

#endif // !YXL_ARRAY_QUEUE_H
