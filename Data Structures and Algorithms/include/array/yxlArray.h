/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:00:00
 * \description:
 */

#pragma once

#ifndef YXL_ARRAY_H
#define YXL_ARRAY_H

#include <cstddef>
#include <ostream>

#include "../yxlList.h"

template <typename T, unsigned N = 1 << 10>
class yxlArray final : public yxlList<T>
{
public:
    yxlArray();
    explicit yxlArray(const T& initial_value);
    yxlArray(yxlArray<T, N>& that);
    yxlArray(yxlArray<T, N>&& that) noexcept;
    ~yxlArray() override = default;

    bool empty() const override;
    unsigned size() const override;
    int index_of(const T& value) const override;
    void clear() override;
    void erase(const unsigned& index) override;
    void insert(const unsigned& index, const T& value) override;

    class Iterator;
    Iterator begin();
    Iterator end();

    T& operator[](const unsigned& index);

    yxlArray& operator=(const yxlArray<T, N>& right);
    yxlArray& operator=(yxlArray<T, N>&& right) noexcept;

    template <typename Tt, unsigned Nn>
    friend std::ostream& operator<<(std::ostream& out, const yxlArray<Tt, Nn>& item);

private:
    T* array_;
    unsigned size_;
    unsigned max_size_;

    void change_size(const unsigned& new_size);
    bool check_index(const unsigned& index) const;
};

template <typename T, unsigned N>
class yxlArray<T, N>::Iterator
{
public:
    using _Mybase = Iterator;
    using iterator_category = std::random_access_iterator_tag;

    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using reference = T &;


    Iterator() = default;
    explicit Iterator(T* that);
    Iterator(const Iterator& that);
    Iterator(Iterator&& that) noexcept;
    ~Iterator() = default;

    T& operator*() const;
    T* operator->() const;

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    Iterator operator+(const int& right) const;
    Iterator operator-(const int& right) const;

    bool operator<(const Iterator& right) const;
    bool operator>(const Iterator& right) const;
    bool operator<=(const Iterator& right) const;
    bool operator>=(const Iterator& right) const;
    bool operator!=(const Iterator& right) const;
    bool operator==(const Iterator& right) const;

    Iterator& operator=(const Iterator& right) = default;
    Iterator& operator=(Iterator&& right) noexcept = default;
    Iterator& operator+=(const int& right);
    Iterator& operator-=(const int& right);

private:
    T* position_;
};

template <typename T, unsigned N>
yxlArray<T, N>::yxlArray()
{
    size_ = 0;
    max_size_ = N;
    array_ = new T[max_size_];
}

template <typename T, unsigned N>
yxlArray<T, N>::yxlArray(const T& initial_value)
{
    size_ = max_size_ = N;
    array_ = new T[max_size_];
    for (auto& i : *this)
    {
        i = initial_value;
    }
}

template <typename T, unsigned N>
yxlArray<T, N>::yxlArray(yxlArray<T, N>& that)
{
    size_ = that.size_;
    max_size_ = that.max_size_;
    array_ = new T[max_size_];
    for (unsigned i = 0; i < size_; ++i)
    {
        array_[i] = that.array_[i];
    }
}

template <typename T, unsigned N>
yxlArray<T, N>::yxlArray(yxlArray<T, N>&& that) noexcept
{
    size_ = that.size_;
    max_size_ = that.max_size_;
    array_ = that.array_;
    that.size_ = 0;
    that.max_size_ = 0;
    that.array_ = nullptr;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::empty() const
{
    return size_ == 0;
}

template <typename T, unsigned N>
unsigned yxlArray<T, N>::size() const
{
    return size_;
}

template <typename T, unsigned N>
int yxlArray<T, N>::index_of(const T& value) const
{
    for (unsigned i = 0; i < size_; ++i)
    {
        if (array_[i] == value) { return i; }
    }
    return -1;
}

template <typename T, unsigned N>
void yxlArray<T, N>::clear()
{
    delete [] array_;
    size_ = 0;
    array_ = new T[max_size_];
}

template <typename T, unsigned N>
void yxlArray<T, N>::erase(const unsigned& index)
{
    if (check_index(index))
    {
        for (auto i = index + 1; i < size_; ++i)
        {
            array_[i - 1] = array_[i];
        }
        array_[size_--].~T();
        if (size_ < (max_size_ >> 1))
        {
            change_size(max_size_ >> 1);
        }
    }
}

template <typename T, unsigned N>
void yxlArray<T, N>::insert(const unsigned& index, const T& value)
{
    if (check_index(index))
    {
        if (size_ == max_size_)
        {
            change_size(max_size_ << 1);
        }
        for (auto i = index; i < size_; ++i)
        {
            array_[i + 1] = array_[i];
        }
        array_[index] = value;
        ++size_;
    }
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::begin()
{
    return Iterator(array_);
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::end()
{
    return Iterator(array_ + size_);
}

template <typename T, unsigned N>
T& yxlArray<T, N>::operator[](const unsigned& index)
{
    if (check_index(index)) { return array_[index]; }
    return array_[0];
}

template <typename T, unsigned N>
yxlArray<T, N>& yxlArray<T, N>::operator=(const yxlArray<T, N>& right)
{
    size_ = right.size_;
    max_size_ = right.max_size_;
    array_ = new T[max_size_];
    for (unsigned i = 0; i < size_; ++i)
    {
        array_[i] = right.array_[i];
    }
    return *this;
}

template <typename T, unsigned N>
yxlArray<T, N>& yxlArray<T, N>::operator=(yxlArray<T, N>&& right) noexcept
{
    size_ = right.size_;
    max_size_ = right.max_size_;
    array_ = right.array_;
    right.size_ = 0;
    right.max_size_ = 0;
    right.array_ = nullptr;
    return *this;
}

template <typename T, unsigned N>
void yxlArray<T, N>::change_size(const unsigned& new_size)
{
    T* temp = new T[new_size];
    for (unsigned i = 0; i < size_; ++i)
    {
        temp[i] = array_[i];
    }
    delete [] array_;
    array_ = temp;
    max_size_ = new_size;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::check_index(const unsigned& index) const
{
    return index >= 0 && index < size_;
}

template <typename T, unsigned N>
yxlArray<T, N>::Iterator::Iterator(T* that)
{
    position_ = that;
}

template <typename T, unsigned N>
yxlArray<T, N>::Iterator::Iterator(const Iterator& that)
{
    position_ = that.position_;
}

template <typename T, unsigned N>
yxlArray<T, N>::Iterator::Iterator(Iterator&& that) noexcept
{
    position_ = that.position_;
    that.position_ = nullptr;
}

template <typename T, unsigned N>
T& yxlArray<T, N>::Iterator::operator*() const
{
    return *position_;
}

template <typename T, unsigned N>
T* yxlArray<T, N>::Iterator::operator->() const
{
    return &*position_;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator++()
{
    ++position_;
    return *this;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator++(int)
{
    Iterator old = *this;
    ++position_;
    return old;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator--()
{
    --position_;
    return *this;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator--(int)
{
    Iterator old = *this;
    --position_;
    return old;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator+(const int& right) const
{
    Iterator old = *this;
    old.position_ += right;
    return old;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator-(const int& right) const
{
    Iterator old = *this;
    old.position_ -= right;
    return old;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::Iterator::operator<(const Iterator& right) const
{
    return position_ < right.position_;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::Iterator::operator>(const Iterator& right) const
{
    return position_ > right.position_;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::Iterator::operator>=(const Iterator& right) const
{
    return position_ >= right.position_;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::Iterator::operator<=(const Iterator& right) const
{
    return position_ <= right.position_;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::Iterator::operator!=(const Iterator& right) const
{
    return position_ != right.position_;
}

template <typename T, unsigned N>
bool yxlArray<T, N>::Iterator::operator==(const Iterator& right) const
{
    return position_ == right.position_;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator+=(const int& right)
{
    position_ += right;
    return *this;
}

template <typename T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator-=(const int& right)
{
    position_ -= right;
    return *this;
}

template <typename T, unsigned N>
std::ostream& operator<<(std::ostream& out, const yxlArray<T, N>& item)
{
    for (unsigned i = 0; i < item.size_; ++i)
    {
        out << item.array_[i] << ' ';
    }
    return out;
}

#endif // !YXL_ARRAY_H
