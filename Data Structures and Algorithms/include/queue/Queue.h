/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 14:14:10
 * \Description:
 */

#pragma once

#ifndef QUEUE_H
#define QUEUE_H

namespace yxl
{
	template <typename T>
	class Queue
	{
	public:
		Queue() = default;
		virtual ~Queue() = default;
		Queue(Queue<T>& that) noexcept = default;
		Queue(Queue<T>&& that) noexcept = default;

		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual T& front() const = 0;
		virtual T& back() const = 0;
		virtual void clear() = 0;
		virtual void pop() = 0;
		virtual void push_front(const T& value) = 0;
		virtual void push_back(const T& value) = 0;

		Queue& operator=(const Queue<T>& right) = default;
		Queue& operator=(Queue<T>&& right) noexcept = default;
	};
}

#endif // !QUEUE_H
