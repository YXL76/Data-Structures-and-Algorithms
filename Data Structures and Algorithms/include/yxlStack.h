/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:09:30
 * \description:
 */

#pragma once

#ifndef YXL_STACK_H
#define YXL_STACK_H

#include "yxlLinearContainer.h"

template<typename T>
class yxlStack : public yxlLinearContainer<T>
{
public:
    yxlStack() = default;
    virtual ~yxlStack() = default;
    yxlStack(yxlStack<T>& that) noexcept = default;
    yxlStack(yxlStack<T>&& that) noexcept = default;

    virtual bool empty() const override = 0;
    virtual unsigned size() const override = 0;
    virtual T& top() const = 0;
    virtual void clear() override = 0;
    virtual void pop() = 0;
    virtual void push(const T& value) = 0;

    yxlStack& operator=(const yxlStack<T>& right) = default;
    yxlStack& operator=(yxlStack<T>&& right) noexcept = default;
};

#endif // !YXL_STACK_H
