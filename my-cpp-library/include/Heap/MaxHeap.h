#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/20 20:49:08
 * \Description:
 */

#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "Heap.h"
#include <ostream>

namespace yxl
{
    template <typename T>
    class MaxHeap final : public Heap<T>
    {
    public:
        MaxHeap();
        explicit MaxHeap(const int& initial_size);
        MaxHeap(const MaxHeap<T>& that);
        MaxHeap(MaxHeap<T>&& that) noexcept;
        ~MaxHeap();

        bool empty() const override;
        int size() const override;
        const T& top() override;
        void pop() override;
        void push(const T& value) override;

        MaxHeap& operator=(const MaxHeap<T>& right);
        MaxHeap& operator=(MaxHeap<T>&& right) noexcept;

    private:
        T* heap_;
        int size_;
        int max_size_;

        static int parent(const int& index);
        static int left(const int& index);
        static int right(const int& index);
        void change_size(const int& new_size);
    };

    template <typename T>
    MaxHeap<T>::MaxHeap(): size_(0), max_size_(1 << 10)
    {
        heap_ = new T [max_size_];
    }

    template <typename T>
    MaxHeap<T>::MaxHeap(const int& initial_size): size_(0), max_size_(initial_size)
    {
        heap_ = new T [initial_size];
    }

    template <typename T>
    MaxHeap<T>::MaxHeap(const MaxHeap<T>& that)
    {
        *this = that;
    }

    template <typename T>
    MaxHeap<T>::MaxHeap(MaxHeap<T>&& that) noexcept
    {
        *this = std::move(that);
    }

    template <typename T>
    MaxHeap<T>::~MaxHeap()
    {
        delete [] heap_;
        heap_ = nullptr;
        size_ = max_size_ = 0;
    }

    template <typename T>
    bool MaxHeap<T>::empty() const
    {
        return size_ == 0;
    }

    template <typename T>
    int MaxHeap<T>::size() const
    {
        return size_;
    }

    template <typename T>
    const T& MaxHeap<T>::top()
    {
        if (size_ == 0)
        {
        }
        return heap_[0];
    }

    template <typename T>
    void MaxHeap<T>::pop()
    {
        if (size_ == 0) { return; }
        T last = heap_[--size_];
        auto current = 0, child = 1;
        while (child < size_)
        {
            if (child < size_ - 1 && heap_[child] < heap_[child + 1]) { ++child; }
            if (last >= heap_[child]) { break; }
            heap_[current] = heap_[child];
            current = child;
            child = left(child);
        }
        heap_[current] = last;
    }

    template <typename T>
    void MaxHeap<T>::push(const T& value)
    {
        if (size_ == max_size_){change_size(size_ << 1);}
        auto current = size_++; 
        heap_[current] = value; 
        while (current != 0 && heap_[parent(current)] < heap_[current]) 
        {
            std::swap(heap_[current], heap_[parent(current)]); 
            current = parent(current); 
        } 
    }

    template <typename T>
    MaxHeap<T>& MaxHeap<T>::operator=(const MaxHeap<T>& right)
    {
        size_ = right.size_;
        max_size_ = right.max_size_;
        delete [] heap_;
        heap_ = new T [max_size_];
        for (auto i = 0; i < max_size_; ++i)
        {
            heap_[i] = right.heap_[i];
        }
        return *this;
    }

    template <typename T>
    MaxHeap<T>& MaxHeap<T>::operator=(MaxHeap<T>&& right) noexcept
    {
        heap_ = right.heap_;
        size_ = right.size_;
        max_size_ = right.max_size_;
        right.heap_ = nullptr;
        right.size_ = right.max_size_ = 0;
        return *this;
    }

    template <typename T>
    int MaxHeap<T>::parent(const int& index)
    {
        return (index - 1) >> 1;
    }

    template <typename T>
    int MaxHeap<T>::left(const int& index)
    {
        return index << 1 | 1;
    }

    template <typename T>
    int MaxHeap<T>::right(const int& index)
    {
        return (index << 1) + 2;
    }

    template <typename T>
    void MaxHeap<T>::change_size(const int& new_size)
    {
        T* temp = new T[new_size];
        for (auto i = 0; i < size_ && i < new_size; ++i)
        {
            temp[i] = heap_[i];
        }
        delete [] heap_;
        heap_ = temp;
        max_size_ = new_size;
    }
}

#endif // !MAX_HEAP_H
