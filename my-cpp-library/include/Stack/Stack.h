#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:09:30
 * \Description:
 */

#ifndef STACK_H
#define STACK_H

namespace yxl
{
	template <typename T>
	class Stack
	{
	public:
		Stack() = default;
		virtual ~Stack() = default;
		Stack(const Stack<T>& that) noexcept = default;
		Stack(Stack<T>&& that) noexcept = default;

		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual T& top() const = 0;
		virtual void clear() = 0;
		virtual void pop() = 0;
		virtual void push(const T& value) = 0;

		Stack& operator=(const Stack<T>& right) = default;
		Stack& operator=(Stack<T>&& right) noexcept = default;
	};
} // namespace yxl

#endif // !STACK_H
