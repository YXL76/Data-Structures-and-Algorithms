#pragma once

//Author: YXL
//last_write: 2018/03/02 6:04:44

#ifndef YXL_ARRAY_H
#define YXL_ARRAY_H

#include <cstddef>
#include <ostream>

template <class T, unsigned N>
class yxlArray
{
public:
    yxlArray();
    explicit yxlArray(T initial_value);
    yxlArray(yxlArray& that);
    yxlArray(yxlArray&& that) noexcept;
    ~yxlArray();

    bool empty() const;
    unsigned size() const;

    class Iterator;
    Iterator begin();
    Iterator end();

    T& operator[](const unsigned& index);

    yxlArray& operator=(const yxlArray& right);
    yxlArray& operator=(yxlArray&& right) noexcept;

    template <class Tt, unsigned Nn>
    friend std::ostream& operator<<(std::ostream& out, const yxlArray<Tt, Nn>& item); // NOLINT(readability-redundant-declaration)

private:
    T* array_;
    unsigned size_;
    
    bool check_index(const unsigned & index) const;
};

template <class T, unsigned N>
class yxlArray<T, N>::Iterator
{
public:
    // ReSharper disable once CppInconsistentNaming
    using _Mybase = typename yxlArray<T, N>::Iterator;
    using iterator_category = std::random_access_iterator_tag;

    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T * ;
    using reference = T & ;


    Iterator();
    explicit Iterator(T* that);
    Iterator(const Iterator& that);
    Iterator(Iterator&& that) noexcept;
    ~Iterator();

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

    Iterator& operator=(const Iterator& right);
    Iterator& operator=(Iterator&& right) noexcept;
    Iterator& operator+=(const int& right);
    Iterator& operator-=(const int& right);

private:
    T* position_;
};

template <class T, unsigned N>
yxlArray<T, N>::yxlArray()
{
    size_ = N;
    array_ = new T[size_];
}

template <class T, unsigned N>
yxlArray<T, N>::yxlArray(const T initial_value)
{
    size_ = N;
    array_ = new T[size_];
    for (auto& i : *this)
    {
        i = initial_value;
    }
}

template <class T, unsigned N>
yxlArray<T, N>::yxlArray(yxlArray& that)
{
    size_ = that.size_;
    array_ = new T[size_];
    for (auto i = begin(), j = that.begin(); i < end(); ++i, ++j)
    {
        *i = *j;
    }
}

template <class T, unsigned N>
yxlArray<T, N>::yxlArray(yxlArray&& that) noexcept
{
    size_ = that.size_;
    array_ = that.array_;
    that.array_ = nullptr;
}

template <class T, unsigned N>
yxlArray<T, N>::~yxlArray()
{
    delete[] array_;
}

template <class T, unsigned N>
bool yxlArray<T, N>::empty() const
{
    return size_ == 0;
}

template <class T, unsigned N>
unsigned yxlArray<T, N>::size() const
{
    return size_;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::begin()
{
    return Iterator(array_);
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::end()
{
    return Iterator(array_ + size_);
}

template <class T, unsigned N>
T& yxlArray<T, N>::operator[](const unsigned& index)
{
    if (check_index(index))  return array_[index];
    return array_[0];
}

template <class T, unsigned N>
yxlArray<T, N>& yxlArray<T, N>::operator=(const yxlArray& right)
{
    if (this != &right)
    {
        size_ = right.size_;
        array_ = new T[size_];
        for (auto i = begin(), j = right.begin(); i < end(); ++i, ++j)
        {
            *i = *j;
        }
    }
    return *this;
}

template <class T, unsigned N>
yxlArray<T, N>& yxlArray<T, N>::operator=(yxlArray&& right) noexcept
{
    if (this != &right)
    {
        size_ = right.size_;
        array_ = right.array_;
        right.size_ = 0;
        right.array_ = nullptr;
    }
    return *this;
}

template <class T, unsigned N>
bool yxlArray<T, N>::check_index(const unsigned& index) const
{
    return index >= 0 && index < size_;
}

template <class T, unsigned N>
yxlArray<T, N>::Iterator::Iterator() : position_(nullptr)
{
}

template <class T, unsigned N>
yxlArray<T, N>::Iterator::Iterator(T* that)
{
    position_ = that;
}

template <class T, unsigned N>
yxlArray<T, N>::Iterator::Iterator(const Iterator& that)
{
    position_ = that.position_;
}

template <class T, unsigned N>
yxlArray<T, N>::Iterator::Iterator(Iterator&& that) noexcept
{
    position_ = that.position_;
    that.position_ = nullptr;
}

template <class T, unsigned N>
yxlArray<T, N>::Iterator::~Iterator()
= default;

template <class T, unsigned N>
T& yxlArray<T, N>::Iterator::operator*() const
{
    return *position_;
}

template <class T, unsigned N>
T* yxlArray<T, N>::Iterator::operator->() const
{
    return &*position_;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator++()
{
    ++position_;
    return *this;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator++(int)
{
    Iterator old = *this;
    ++position_;
    return old;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator--()
{
    --position_;
    return *this;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator--(int)
{
    Iterator old = *this;
    --position_;
    return old;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator+(const int& right) const
{
    Iterator old = *this;
    old.position_ += right;
    return old;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator yxlArray<T, N>::Iterator::operator-(const int& right) const
{
    Iterator old = *this;
    old.position_ -= right;
    return old;
}

template <class T, unsigned N>
bool yxlArray<T, N>::Iterator::operator<(const Iterator& right) const
{
    return position_ < right.position_;
}

template <class T, unsigned N>
bool yxlArray<T, N>::Iterator::operator>(const Iterator& right) const
{
    return position_ > right.position_;
}

template <class T, unsigned N>
bool yxlArray<T, N>::Iterator::operator>=(const Iterator& right) const
{
    return position_ >= right.position_;
}

template <class T, unsigned N>
bool yxlArray<T, N>::Iterator::operator<=(const Iterator& right) const
{
    return position_ <= right.position_;
}

template <class T, unsigned N>
bool yxlArray<T, N>::Iterator::operator!=(const Iterator& right) const
{
    return position_ != right.position_;
}

template <class T, unsigned N>
bool yxlArray<T, N>::Iterator::operator==(const Iterator& right) const
{
    return position_ == right.position_;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator=(const Iterator& right)
{
    if (this != &right) position_ == right.position_;
    return *this;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator=(Iterator&& right) noexcept
{
    if (this != &right)
    {
        position_ == right.position_;
        right.position_ = nullptr;
    }
    return *this;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator+=(const int& right)
{
    this->position_ += right;
    return *this;
}

template <class T, unsigned N>
typename yxlArray<T, N>::Iterator& yxlArray<T, N>::Iterator::operator-=(const int& right)
{
    this->position_ -= right;
    return *this;
}

template <class T, unsigned N>
std::ostream& operator<<(std::ostream& out, const yxlArray<T, N>& item)
{
    for (unsigned i = 0; i < item.size_; ++i)
    {
        out << item.array_[i] << ' ';
    }
    return out;
}

#endif // !YXL_ARRAY_H
