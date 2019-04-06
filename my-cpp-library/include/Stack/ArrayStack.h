#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:24:20
 * \Description:
 */

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "Stack.h"

namespace yxl
{
    template <typename T>
    class ArrayStack final : public Stack<T>,
                             public Array<T>
    {
    public:
        constexpr ArrayStack() = default;
        ArrayStack(const ArrayStack<T>& that);
        ArrayStack(ArrayStack<T>&& that) noexcept;
        ~ArrayStack() override = default;

        T& top() const override;
        void pop() override;
        void push(const T& value) override;

        ArrayStack& operator=(const ArrayStack<T>& right) = default;
        ArrayStack& operator=(ArrayStack<T>&& right) noexcept = default;

    private:
        int index_of(const T& /*value*/) const override { return 0; }
        void erase(const int& index) override {}
        void insert(const int& index, const T& value) override {}
    };

    template <typename T>
    ArrayStack<T>::ArrayStack(const ArrayStack<T>& that)
    {
        *this = that;
    }

    template <typename T>
    ArrayStack<T>::ArrayStack(ArrayStack<T>&& that) noexcept
    {
        *this = std::move(that);
    }

    template <typename T>
    T& ArrayStack<T>::top() const
    {
        if (this->size_ > 0) { return this->array_[this->size_ - 1]; }
        return this->array_[0];
    }

    template <typename T>
    void ArrayStack<T>::pop()
    {
        if (this->size_ > 0) { --this->size_; }
    }

    template <typename T>
    void ArrayStack<T>::push(const T& value)
    {
        if (this->size_ == this->max_size_) { this->change_size(this->size_ << 1); }
        this->array_[this->size_++] = value;
    }
} // namespace yxl

#endif // !ARRAY_STACK_H
