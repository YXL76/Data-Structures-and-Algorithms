#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/04 13:50:10
 * \Description:
 */

#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "Queue.h"
#include "../List/Array.h"

namespace yxl
{
    template <typename T>
    class ArrayQueue final : public Queue<T>,
                             public Array<T>
    {
    public:
        ArrayQueue() = default;
        ArrayQueue(const ArrayQueue<T>& that);
        ArrayQueue(ArrayQueue<T>&& that) noexcept;
        ~ArrayQueue() override = default;

        T& front() const override;
        T& back() const override;
        void pop_front() override;
        void pop_back() override;
        void push_front(const T& value) override;
        void push_back(const T& value) override;

        ArrayQueue& operator=(const ArrayQueue<T>& right);
        ArrayQueue& operator=(ArrayQueue<T>&& right) noexcept;

    private:
        int front_{0};

        int index_of(const T& /*value*/) const override { return 0; }
        void erase(const int& index) override {}
        void insert(const int& index, const T& value) override {}
    };

    template <typename T>
    ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& that)
    {
        *this = that;
    }

    template <typename T>
    ArrayQueue<T>::ArrayQueue(ArrayQueue<T>&& that) noexcept
    {
        *this = std::move(that);
    }

    template <typename T>
    T& ArrayQueue<T>::front() const
    {
        return this->array_[front_];
    }

    template <typename T>
    T& ArrayQueue<T>::back() const
    {
        return this->array_[(front_ + this->size_ - 1) % this->max_size_];
    }

    template <typename T>
    void ArrayQueue<T>::pop_front()
    {
        if (this->size_ != 0)
        {
            --this->size_;
            front_ = (front_ + 1) % this->max_size_;
        }
    }

    template <typename T>
    void ArrayQueue<T>::pop_back()
    {
        if (this->size_ != 0)
        {
            --this->size_;
        }
    }

    template <typename T>
    void ArrayQueue<T>::push_front(const T& value)
    {
        if (this->size_ == this->max_size_) { this->change_size(this->max_size_ << 1); }
        front_ = (front_ + this->max_size_ - 1) % this->max_size_;
        this->array_[front_] = value;
        ++this->size_;
    }

    template <typename T>
    void ArrayQueue<T>::push_back(const T& value)
    {
        if (this->size_ == this->max_size_) { this->change_size(this->max_size_ << 1); }
        this->array_[(front_ + this->size_) % this->max_size_] = value;
        ++this->size_;
    }

    template <typename T>
    ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& right)
    {
        front_ = right.front_;
        delete [] this->array_;
        this->size_ = right.size_;
        this->max_size_ = right.max_size_;
        this->array_ = new T[this->max_size_];
        for (auto i = 0; i < this->max_size_; ++i)
        {
            this->array_[i] = right.array_[i];
        }
        return *this;
    }

    template <typename T>
    ArrayQueue<T>& ArrayQueue<T>::operator=(ArrayQueue<T>&& right) noexcept
    {
        front_ = right.front_;
        this->size_ = right.size_;
        this->max_size_ = right.max_size_;
        this->array_ = right.array_;
        right.front_ = 0;
        right.size_ = 0;
        right.max_size_ = 0;
        right.array_ = nullptr;
        return *this;
    }
} // namespace yxl

#endif // !ARRAY_QUEUE_H
