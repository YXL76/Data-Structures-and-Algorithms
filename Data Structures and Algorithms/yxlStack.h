/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:09:30
 * \description:
 */

#pragma once

#ifndef YXL_STACK_H
#define YXL_STACK_H

template<typename T>
class yxlStack
{
public:
    yxlStack() = default;
    virtual ~yxlStack() = default;
    yxlStack(yxlStack& that) noexcept = default;
    yxlStack(yxlStack&& that) noexcept = default;

    virtual bool empty() const = 0;
    virtual unsigned size() const = 0;
    virtual T& top() const = 0;
    virtual void clear() = 0;
    virtual void pop() = 0;
    virtual void push(const T& value) = 0;

    yxlStack& operator=(const yxlStack& right) = default;
    yxlStack& operator=(yxlStack&& right) noexcept = default;
};

#endif // !YXL_STACK_H
