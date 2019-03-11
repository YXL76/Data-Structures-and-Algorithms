/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 16:01:40
 * \description:
 */

#pragma once

#ifndef YXL_CHAIN_H
#define YXL_CHAIN_H

#include "yxlList.h"

template <typename T>
class yxlChain final : public yxlList<T>
{
public:
    yxlChain();
    yxlChain(yxlChain<T>& that);
    yxlChain(yxlChain<T>&& that) noexcept;
    ~yxlChain() override = default;

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

    yxlChain& operator=(const yxlChain<T>& right);
    yxlChain& operator=(yxlChain<T>&& right) noexcept;

    template <typename Tt>
    friend std::ostream& operator<<(std::ostream& out, const yxlChain<Tt>& item);

    struct Node
    {
        T value;
        Node* next;

        Node();
        explicit Node(const T& value);
        Node(const T& value, Node* next);
    };

private:
    unsigned size_;
    Node* head_node_;
    Node* rear_node_;

    bool check_index(const unsigned& index) const;
};

template <typename T>
class yxlChain<T>::Iterator
{
public:
    using _Mybase = Iterator;
    using iterator_category = std::forward_iterator_tag;

    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using reference = T &;


    Iterator() = default;
    explicit Iterator(Node* that);
    Iterator(const Iterator& that);
    Iterator(Iterator&& that) noexcept;
    ~Iterator() = default;

    Node& operator*() const;
    Node* operator->() const;

    Iterator& operator++();
    Iterator operator++(int);

    Iterator operator+(const int& right) const;

    bool operator!=(const Iterator& right) const;
    bool operator==(const Iterator& right) const;

    Iterator& operator=(const Iterator& right) = default;
    Iterator& operator=(Iterator&& right) noexcept = default;
    Iterator& operator+=(const int& right);

private:
    Node* position_;
};

template <typename T>
yxlChain<T>::yxlChain(): size_(0)
{
    head_node_ = new Node();
    rear_node_ = new Node();
    rear_node_->next = head_node_;
    head_node_->next = rear_node_;
}

template <typename T>
yxlChain<T>::yxlChain(yxlChain<T>& that)
{
    size_ = that.size_;
    head_node_ = new Node(that.head_node_->value);
    rear_node_ = new Node(that.rear_node_->value);
    rear_node_->next = head_node_;
    head_node_->next = rear_node_;
    Node* this_node = head_node_;
    Node* that_node = that.head_node_;
    for (unsigned i = 0; i < size_; ++i)
    {
        that_node = that_node->next;
        this_node->next = new Node(that_node->value, this_node->next);
        this_node = this_node->next;
    }
}

template <typename T>
yxlChain<T>::yxlChain(yxlChain<T>&& that) noexcept
{
    size_ = that.size_;
    head_node_ = that.head_node_;
    rear_node_ = that.rear_node_;
    that.size_ = 0;
    that.head_node_ = nullptr;
    that.rear_node_ = nullptr;
}

template <typename T>
bool yxlChain<T>::empty() const
{
    return size_ == 0;
}

template <typename T>
unsigned yxlChain<T>::size() const
{
    return size_;
}

template <typename T>
int yxlChain<T>::index_of(const T& value) const
{
    auto index = 0;
    Node* current_node = head_node_->next;
    while (current_node != rear_node_ && current_node->value != value)
    {
        current_node = current_node->next;
        ++index;
    }
    if (current_node == rear_node_) return -1;
    return index;
}

template <typename T>
void yxlChain<T>::clear()
{
    Node* previous_node = head_node_;
    Node* current_node = head_node_->next;
    for (unsigned i = 0; i < size_; ++i)
    {
        delete previous_node;
        previous_node = current_node;
        current_node = current_node->next;
    }
    delete previous_node;
    delete current_node;
    size_ = 0;
    head_node_ = new Node();
    rear_node_ = new Node();
    rear_node_->next = head_node_;
    head_node_->next = rear_node_;
}

template <typename T>
void yxlChain<T>::erase(const unsigned& index)
{
    if (check_index(index))
    {
        Node* current_node;
        if (index == 0) { current_node = head_node_; }
        else { current_node = head_node_->next; }
        for (unsigned i = 1; i < index; ++i)
        {
            current_node = current_node->next;
        }
        Node* erase_node = current_node->next;
        current_node->next = current_node->next->next;
        delete erase_node;
        --size_;
    }
}

template <typename T>
void yxlChain<T>::insert(const unsigned& index, const T& value)
{
    if (check_index(index) || index == size_)
    {
        Node* current_node = head_node_;
        for (unsigned i = 0; i < index; ++i)
        {
            current_node = current_node->next;
        }
        current_node->next = new Node(value, current_node->next);
        ++size_;
    }
}

template <typename T>
typename yxlChain<T>::Iterator yxlChain<T>::begin()
{
    return Iterator(head_node_->next);
}

template <typename T>
typename yxlChain<T>::Iterator yxlChain<T>::end()
{
    return Iterator(rear_node_);
}

template <typename T>
T& yxlChain<T>::operator[](const unsigned& index)
{
    if (check_index(index))
    {
        Node* current_node = head_node_->next;
        for (unsigned i = 0; i < index; ++i)
        {
            current_node = current_node->next;
        }
        return current_node->value;
    }
    return head_node_->value;
}

template <typename T>
yxlChain<T>& yxlChain<T>::operator=(const yxlChain<T>& right)
{
    size_ = right.size_;
    head_node_ = new Node(right.head_node_->value);
    rear_node_ = new Node(right.rear_node_->value);
    rear_node_->next = head_node_;
    head_node_->next = rear_node_;
    Node* this_node = head_node_;
    Node* that_node = right.head_node_;
    for (unsigned i = 0; i < size_; ++i)
    {
        that_node = that_node->next;
        this_node->next = new Node(that_node->value, this_node->next);
        this_node = this_node->next;
    }
    return *this;
}

template <typename T>
yxlChain<T>& yxlChain<T>::operator=(yxlChain<T>&& right) noexcept
{
    size_ = right.size_;
    head_node_ = right.head_node_;
    rear_node_ = right.rear_node_;
    right.size_ = 0;
    right.head_node_ = nullptr;
    right.rear_node_ = nullptr;
    return *this;
}

template <typename T>
yxlChain<T>::Node::Node(): next(nullptr)
{
}

template <typename T>
yxlChain<T>::Node::Node(const T& value): next(nullptr)
{
    this->value = value;
}

template <typename T>
yxlChain<T>::Node::Node(const T& value, Node* next)
{
    this->value = value;
    this->next = next;
}

template <typename T>
bool yxlChain<T>::check_index(const unsigned& index) const
{
    return index >= 0 && index < size_;
}

template <typename T>
yxlChain<T>::Iterator::Iterator(Node* that)
{
    position_ = that;
}

template <typename T>
yxlChain<T>::Iterator::Iterator(const Iterator& that)
{
    position_ = that.position_;
}

template <typename T>
yxlChain<T>::Iterator::Iterator(Iterator&& that) noexcept
{
    position_ = that.position_;
    that.position_ = nullptr;
}

template <typename T>
typename yxlChain<T>::Node& yxlChain<T>::Iterator::operator*() const
{
    return *position_;
}

template <typename T>
typename yxlChain<T>::Node* yxlChain<T>::Iterator::operator->() const
{
    return &*position_;
}

template <typename T>
typename yxlChain<T>::Iterator& yxlChain<T>::Iterator::operator++()
{
    position_ = position_->next;
    return *this;
}

template <typename T>
typename yxlChain<T>::Iterator yxlChain<T>::Iterator::operator++(int)
{
    Iterator old = *this;
    position_ = position_->next;
    return old;
}

template <typename T>
typename yxlChain<T>::Iterator yxlChain<T>::Iterator::operator+(const int& right) const
{
    Iterator old = *this;
    for (auto i = 0; i < right; ++i)
    {
        old.position_ = old.position_->next;
    }
    return old;
}

template <typename T>
bool yxlChain<T>::Iterator::operator!=(const Iterator& right) const
{
    return position_ != right.position_;
}

template <typename T>
bool yxlChain<T>::Iterator::operator==(const Iterator& right) const
{
    return position_ == right.position_;
}

template <typename T>
typename yxlChain<T>::Iterator& yxlChain<T>::Iterator::operator+=(const int& right)
{
    for (auto i = 0; i < right; ++i)
    {
        position_ = position_->next;
    }
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const yxlChain<T>& item)
{
    typename yxlChain<T>::template Node* current_node = item.head_node_->next;
    for (unsigned i = 0; i < item.max_size_; ++i)
    {
        out << current_node->value << ' ';
        current_node = current_node->next;
    }
    return out;
}

#endif // !YXL_CHAIN_H
