/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 14:14:10
 * \description:
 */

#pragma once

#ifndef YXL_QUEUE_H
#define YXL_QUEUE_H

template <typename T>
class yxlQueue
{
public:
    yxlQueue() = default;
    virtual ~yxlQueue() = default;
    yxlQueue(yxlQueue<T>& that) noexcept = default;
    yxlQueue(yxlQueue<T>&& that) noexcept = default;

    virtual bool empty() const = 0;
    virtual unsigned size() const = 0;
    virtual T& front() const = 0;
    virtual T& back() const = 0;
    virtual void clear() = 0;
    virtual void pop() = 0;
    virtual void push(const T& value) = 0;

    yxlQueue& operator=(const yxlQueue<T>& right) = default;
    yxlQueue& operator=(yxlQueue<T>&& right) noexcept = default;
};

#endif // !YXL_QUEUE_H
