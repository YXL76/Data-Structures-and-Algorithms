#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 14:14:10
 * \Description:
 */

#ifndef QUEUE_H
#define QUEUE_H

namespace yxl
{
    template <typename T>
    class Queue
    {
    public:
        constexpr Queue() = default;
        virtual ~Queue() = default;
        constexpr Queue(const Queue<T>& that) = default;
        constexpr Queue(Queue<T>&& that) noexcept = default;

        virtual T& front() const = 0;
        virtual T& back() const = 0;
        virtual void pop_front() = 0;
        virtual void pop_back() = 0;
        virtual void push_front(const T& value) = 0;
        virtual void push_back(const T& value) = 0;

        Queue& operator=(const Queue<T>& right) = default;
        Queue& operator=(Queue<T>&& right) noexcept = default;
    };
} // namespace yxl

#endif // !QUEUE_H
