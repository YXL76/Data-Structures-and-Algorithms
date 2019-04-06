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
        constexpr Stack() = default;
        virtual ~Stack() = default;
        constexpr Stack(const Stack<T>& that) = default;
        constexpr Stack(Stack<T>&& that) noexcept = default;

        virtual T& top() const = 0;
        virtual void pop() = 0;
        virtual void push(const T& value) = 0;

        Stack& operator=(const Stack<T>& right) = default;
        Stack& operator=(Stack<T>&& right) noexcept = default;
    };
} // namespace yxl

#endif // !STACK_H
