/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:24:20
 * \description:
 */

#pragma once

#ifndef YXL_ARRAY_STACK_H
#define YXL_ARRAY_STACK_H

#include "yxlStack.h"

template <typename T>
class yxlArrayStack final : public yxlStack<T>
{
public:
    yxlArrayStack();
    yxlArrayStack(yxlArrayStack<T>& that);
    yxlArrayStack(yxlArrayStack<T>&& that) noexcept;
    ~yxlArrayStack() override = default;

    bool empty() const override;
    unsigned size() const override;
    T& top() const override;
    void clear() override;
    void pop() override;
    void push(const T& value) override;

    yxlArrayStack& operator=(const yxlArrayStack<T>& right);
    yxlArrayStack& operator=(yxlArrayStack<T>&& right) noexcept;

private:
    T* array_;
    int top_;
    int size_;

    void change_size();
};

template <typename T>
yxlArrayStack<T>::yxlArrayStack(): top_(-1), size_(1 << 10)
{
    array_ = new T[size_];
}

template <typename T>
yxlArrayStack<T>::yxlArrayStack(yxlArrayStack<T>& that)
{
    size_ = that.size_;
    top_ = that.top_;
    array_ = new T[size_];
    for (auto i = 0; i < size_; ++i)
    {
        array_[i] = that.array_[i];
    }
}

template <typename T>
yxlArrayStack<T>::yxlArrayStack(yxlArrayStack<T>&& that) noexcept
{
    top_ = that.top_;
    size_ = that.size_;
    array_ = that.array_;
    that.top_ = 0;
    that.size_ = 0;
    that.array_ = nullptr;
}

template <typename T>
bool yxlArrayStack<T>::empty() const
{
    return top_ == -1;
}

template <typename T>
unsigned yxlArrayStack<T>::size() const
{
    return static_cast<unsigned int>(top_ + 1);
}

template <typename T>
T& yxlArrayStack<T>::top() const
{
    if (top_ >= 0) { return array_[top_]; }
    return array_[0];
}

template <typename T>
void yxlArrayStack<T>::clear()
{
    delete[] array_;
    top_ = 0;
    size_ = 1 << 10;
    array_ = new T[size_];
}

template <typename T>
void yxlArrayStack<T>::pop()
{
    if (top_ >= 0) { --top_; }
}

template <typename T>
void yxlArrayStack<T>::push(const T& value)
{
    if (top_ == size_ - 1)  {change_size();}
    array_[++top_] = value;
}

template <typename T>
yxlArrayStack<T>& yxlArrayStack<T>::operator=(const yxlArrayStack<T>& right)
{
    size_ = right.size_;
    top_ = right.top_;
    array_ = new T[size_];
    for (auto i = 0; i < size_; ++i)
    {
        array_[i] = right.array_[i];
    }
    return *this;
}

template <typename T>
yxlArrayStack<T>& yxlArrayStack<T>::operator=(yxlArrayStack<T>&& right) noexcept
{
    top_ = right.top_;
    size_ = right.size_;
    array_ = right.array_;
    right.top_ = 0;
    right.size_ = 0;
    right.array_ = nullptr;
    return *this;
}

template <typename T>
void yxlArrayStack<T>::change_size()
{
    T* temp = new T[size_ * 2];
    for (auto i = 0; i < size_; ++i)
    {
        temp[i] = array_[i];
    }
    delete[] array_;
    size_ <<= 1;
    array_ = temp;
}

#endif // !YXL_ARRAY_STACK_H
