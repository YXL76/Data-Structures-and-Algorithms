#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/20 20:49:08
 * \Description:
 */

#ifndef HEAP_H
#define HEAP_H

namespace yxl
{
    template <typename T>
    class Heap
    {
    public:
        constexpr Heap() = default;
        virtual ~Heap() = default;
        constexpr Heap(const Heap<T>& that) = default;
        constexpr Heap(Heap<T>&& that) = default;

        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual const T& top() = 0;
        virtual void pop() = 0;
        virtual void push(const T& value) = 0;

        Heap& operator=(const Heap<T>& right) = default;
        Heap& operator=(Heap<T>&& right) noexcept = default ;
    };
} // namespace yxl

#endif // !HEAP_H
