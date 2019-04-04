#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/17 13:09:50
 * \Description:
 */

#ifndef ARRAY_H
#define ARRAY_H

#include "List.h"
#include <ostream>

namespace yxl
{
    template <typename T>
    class Array : public List<T>
    {
    public:
        Array();
        explicit Array(const int& initial_size);
        Array(const Array<T>& that);
        Array(Array<T>&& that) noexcept;
        ~Array() override = default;

        bool empty() const override;
        int size() const override;
        int index_of(const T& value) const override;
        void clear() override;
        void erase(const int& index) override;
        void insert(const int& index, const T& value) override;

        class Iterator;
        Iterator begin();
        Iterator begin() const;
        Iterator end();
        Iterator end() const;

        T& operator[](const int& index);

        Array& operator=(const Array<T>& right);
        Array& operator=(Array<T>&& right) noexcept;

        template <typename Tt>
        friend std::ostream& operator<<(std::ostream& out, const Array<Tt>& item);
        template <typename Tt>
        friend std::ostream& operator<<(std::ostream& out, Array<Tt>&& item);

    protected:
        T* array_;
        int size_{};
        int max_size_{};

        void change_size(const int& new_size);
        bool check_index(const int& index) const;
    };

    template <typename T>
    class Array<T>::Iterator
    {
    public:
        using _Mybase = Iterator;
        using iterator_category = std::random_access_iterator_tag;

        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;

        Iterator() = default;
        explicit Iterator(T* that);
        explicit Iterator(const T* that);
        Iterator(const Iterator& that);
        Iterator(Iterator&& that) noexcept;
        ~Iterator() = default;

        T& operator*() const;
        T* operator->() const;

        Iterator& operator++();
        const Iterator operator++(int);
        Iterator& operator--();
        const Iterator operator--(int);

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

    template <typename T>
    Array<T>::Array()
    {
        size_ = 0;
        max_size_ = 1 << 10;
        array_ = new T[max_size_];
    }

    template <typename T>
    Array<T>::Array(const int& initial_size)
    {
        size_ = max_size_ = initial_size;
        array_ = new T[max_size_];
    }

    template <typename T>
    Array<T>::Array(const Array<T>& that)
    {
        *this = that;
    }

    template <typename T>
    Array<T>::Array(Array<T>&& that) noexcept
    {
        *this = that;
    }

    template <typename T>
    bool Array<T>::empty() const
    {
        return size_ == 0;
    }

    template <typename T>
    int Array<T>::size() const
    {
        return size_;
    }

    template <typename T>
    int Array<T>::index_of(const T& value) const
    {
        for (auto i = 0; i < size_; ++i)
        {
            if (array_[i] == value) { return i; }
        }
        return -1;
    }

    template <typename T>
    void Array<T>::clear()
    {
        delete [] array_;
        size_ = 0;
        array_ = new T[max_size_];
    }

    template <typename T>
    void Array<T>::erase(const int& index)
    {
        if (check_index(index))
        {
            for (auto i = index + 1; i < size_; ++i)
            {
                array_[i - 1] = array_[i];
            }
            array_[size_--].~T();
            if (size_ < max_size_ >> 1)
            {
                change_size(max_size_ >> 1);
            }
        }
    }

    template <typename T>
    void Array<T>::insert(const int& index, const T& value)
    {
        if (check_index(index) || index == size_)
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

    template <typename T>
    typename Array<T>::Iterator Array<T>::begin()
    {
        return Iterator(array_);
    }

    template <typename T>
    typename Array<T>::Iterator Array<T>::begin() const
    {
        return Iterator(array_);
    }

    template <typename T>
    typename Array<T>::Iterator Array<T>::end()
    {
        return Iterator(array_ + size_);
    }

    template <typename T>
    typename Array<T>::Iterator Array<T>::end() const
    {
        return Iterator(array_ + size_);
    }

    template <typename T>
    T& Array<T>::operator[](const int& index)
    {
        if (check_index(index)) { return array_[index]; }
        return array_[0];
    }

    template <typename T>
    Array<T>& Array<T>::operator=(const Array<T>& right)
    {
        delete [] array_;
        size_ = 0;
        max_size_ = right.max_size_;
        array_ = new T[max_size_];
        for (auto &i : right)
        {
            array_[size_++] = i;
        }
        return *this;
    }

    template <typename T>
    Array<T>& Array<T>::operator=(Array<T>&& right) noexcept
    {
        size_ = right.size_;
        max_size_ = right.max_size_;
        array_ = right.array_;
        right.size_ = 0;
        right.max_size_ = 0;
        right.array_ = nullptr;
        return *this;
    }

    template <typename T>
    void Array<T>::change_size(const int& new_size)
    {
        T* temp = new T[new_size];
        for (auto i = 0; i < size_ && i < new_size; ++i)
        {
            temp[i] = array_[i];
        }
        delete [] array_;
        array_ = temp;
        max_size_ = new_size;
    }

    template <typename T>
    bool Array<T>::check_index(const int& index) const
    {
        return index >= 0 && index < size_;
    }

    template <typename T>
    Array<T>::Iterator::Iterator(T* that)
    {
        position_ = that;
    }

    template <typename T>
    Array<T>::Iterator::Iterator(const T* that)
    {
        position_ = that;
    }

    template <typename T>
    Array<T>::Iterator::Iterator(const Iterator& that)
    {
        position_ = that.position_;
    }

    template <typename T>
    Array<T>::Iterator::Iterator(Iterator&& that) noexcept
    {
        position_ = that.position_;
        that.position_ = nullptr;
    }

    template <typename T>
    T& Array<T>::Iterator::operator*() const
    {
        return *position_;
    }

    template <typename T>
    T* Array<T>::Iterator::operator->() const
    {
        return &*position_;
    }

    template <typename T>
    typename Array<T>::Iterator& Array<T>::Iterator::operator++()
    {
        ++position_;
        return *this;
    }

    template <typename T>
    const typename Array<T>::Iterator Array<T>::Iterator::operator++(int)
    {
        Iterator old = *this;
        ++position_;
        return old;
    }

    template <typename T>
    typename Array<T>::Iterator& Array<T>::Iterator::operator--()
    {
        --position_;
        return *this;
    }

    template <typename T>
    const typename Array<T>::Iterator Array<T>::Iterator::operator--(int)
    {
        Iterator old = *this;
        --position_;
        return old;
    }

    template <typename T>
    typename Array<T>::Iterator Array<T>::Iterator::operator+(const int& right) const
    {
        Iterator old = *this;
        old.position_ += right;
        return old;
    }

    template <typename T>
    typename Array<T>::Iterator Array<T>::Iterator::operator-(const int& right) const
    {
        Iterator old = *this;
        old.position_ -= right;
        return old;
    }

    template <typename T>
    bool Array<T>::Iterator::operator<(const Iterator& right) const
    {
        return position_ < right.position_;
    }

    template <typename T>
    bool Array<T>::Iterator::operator>(const Iterator& right) const
    {
        return position_ > right.position_;
    }

    template <typename T>
    bool Array<T>::Iterator::operator>=(const Iterator& right) const
    {
        return position_ >= right.position_;
    }

    template <typename T>
    bool Array<T>::Iterator::operator<=(const Iterator& right) const
    {
        return position_ <= right.position_;
    }

    template <typename T>
    bool Array<T>::Iterator::operator!=(const Iterator& right) const
    {
        return position_ != right.position_;
    }

    template <typename T>
    bool Array<T>::Iterator::operator==(const Iterator& right) const
    {
        return position_ == right.position_;
    }

    template <typename T>
    typename Array<T>::Iterator& Array<T>::Iterator::operator+=(const int& right)
    {
        position_ += right;
        return *this;
    }

    template <typename T>
    typename Array<T>::Iterator& Array<T>::Iterator::operator-=(const int& right)
    {
        position_ -= right;
        return *this;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const Array<T>& item)
    {
        for (auto& i : item)
        {
            out << i << ' ';
        }
        out << std::endl;
        return out;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, Array<T>&& item)
    {
        for (auto& i : item)
        {
            out << i << ' ';
        }
        out << std::endl;
        return out;
    }
} // namespace yxl

#endif // !ARRAY_H
