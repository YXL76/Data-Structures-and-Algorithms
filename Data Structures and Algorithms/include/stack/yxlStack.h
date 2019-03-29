/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:09:30
 * \Description:
 */

#pragma once

#ifndef YXL_STACK_H
#define YXL_STACK_H

template <typename T>
class yxlStack
{
public:
    yxlStack() = default;
    virtual ~yxlStack() = default;
    yxlStack(yxlStack<T>& that) noexcept = default;
    yxlStack(yxlStack<T>&& that) noexcept = default;

    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& top() const = 0;
    virtual void clear() = 0;
    virtual void pop() = 0;
    virtual void push(const T& value) = 0;

    yxlStack& operator=(const yxlStack<T>& right) = default;
    yxlStack& operator=(yxlStack<T>&& right) noexcept = default;
};

#endif // !YXL_STACK_H
