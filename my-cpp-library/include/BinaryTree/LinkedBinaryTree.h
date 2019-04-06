#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/05 13:00:00
 * \Description:
 */

#ifndef LINKED_BINARY_TREE_H
#define LINKED_BINARY_TREE_H

#include "BinaryTree.h"
#include "BinaryTreeTask.h"
#include "LinkedBinaryTreeNode.h"
#include "../Queue/ArrayQueue.h"
#include "../Stack/ArrayStack.h"
#include <utility>
#include <functional>

namespace yxl
{
    template <typename T>
    class LinkedBinaryTree : public BinaryTree<LinkedBinaryTreeNode<T>>
    {
    public:
        enum Type { kPre, kIn, kPost, kLevel };

        using tree_node = LinkedBinaryTreeNode<T>;
        using traversal_task = BinaryTreeTask<LinkedBinaryTreeNode<T>*>;

        using ttask = std::function<void(tree_node*&)>;
        using itask = std::function<void(int&)>;
        using iitask = std::function<void(int&, const int&)>;
        using ittask = std::function<void(int&, tree_node*&)>;

        constexpr LinkedBinaryTree();
        explicit LinkedBinaryTree(const T& value);
        LinkedBinaryTree(T that[], const int& size);
        LinkedBinaryTree(const LinkedBinaryTree<T>& that);
        LinkedBinaryTree(LinkedBinaryTree<T>&& that) noexcept;
        ~LinkedBinaryTree() override;

        class Iterator;
        Iterator begin();
        Iterator begin() const;
        Iterator end();
        Iterator end() const;

        virtual bool empty() { return empty(root_); }
        virtual int size() { return size(root_); }
        int height() { return height(root_); }
        int width() { return width(root_); }
        void clear() { return clear(root_); }
        void print(const int& type);

        void unite(const T& value, LinkedBinaryTree& left, LinkedBinaryTree& right);

        bool empty(tree_node*& node) override;
        int size(tree_node*& node) override;
        int height(tree_node*& node) override;
        int width(tree_node*& node) override;
        void clear(tree_node*& node) override;
        void build(tree_node*& node, tree_node* const& that) override;
        void traversal(tree_node*& node, ttask& pre, ttask& in, ttask& post) override;
        void level_traversal(tree_node*& node, int& count, ittask& point, iitask& line, itask& plane) override;

        bool operator!=(const LinkedBinaryTree& right);
        bool operator==(const LinkedBinaryTree& right);

        LinkedBinaryTree& operator=(const LinkedBinaryTree& right);
        LinkedBinaryTree& operator=(LinkedBinaryTree&& right) noexcept;

    protected:
        int size_{0};
        tree_node* root_;

        typename traversal_task::ITask i_task_;
        typename traversal_task::IiTask ii_task_;
        typename traversal_task::ItTask it_task_;

    private:
        void build(tree_node*& node, T that[], int index);
    };

    template <typename T>
    class LinkedBinaryTree<T>::Iterator
    {
    public:
        using tree_node = LinkedBinaryTreeNode<T>;

        using _Mybase = Iterator;
        using iterator_category = std::forward_iterator_tag;

        using value_type = tree_node;
        using difference_type = ptrdiff_t;
        using pointer = tree_node *;
        using const_pointer = const tree_node *;
        using reference = tree_node &;
        using const_reference = const tree_node &;

        Iterator();
        explicit Iterator(const int& type);
        explicit Iterator(tree_node* that);
        Iterator(tree_node* that, const int& type);
        explicit Iterator(const tree_node* that);
        explicit Iterator(const tree_node* that, const int& type);
        Iterator(const Iterator& that);
        Iterator(Iterator&& that) noexcept;
        ~Iterator() = default;

        constexpr explicit operator pointer() const;

        constexpr tree_node& operator*() const;
        constexpr tree_node* operator->() const;

        Iterator& operator++();
        const Iterator operator++(int);

        constexpr bool operator!=(const Iterator& right) const;
        constexpr bool operator==(const Iterator& right) const;

        Iterator& operator=(const Iterator& right);
        Iterator& operator=(Iterator&& right) noexcept;

    private:
        int type_{};
        tree_node* cursor_;
        tree_node* position_;
        ArrayQueue<std::pair<tree_node*, bool>> q_;

        void initialize();
    };

    template <typename T>
    constexpr LinkedBinaryTree<T>::LinkedBinaryTree(): root_(nullptr)
    {
    }

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(const T& value): root_(nullptr)
    {
        size_ = 1;
        root_ = new tree_node(value);
    }

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(T that[], const int& size)
    {
        size_ = size;
        build(root_, that, 1);
    }

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(const LinkedBinaryTree<T>& that)
    {
        *this = that;
    }

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(LinkedBinaryTree<T>&& that) noexcept
    {
        *this = std::move(that);
    }

    template <typename T>
    LinkedBinaryTree<T>::~LinkedBinaryTree()
    {
        clear();
    }

    template <typename T>
    typename LinkedBinaryTree<T>::Iterator LinkedBinaryTree<T>::begin()
    {
        return Iterator(root_);
    }

    template <typename T>
    typename LinkedBinaryTree<T>::Iterator LinkedBinaryTree<T>::begin() const
    {
        return Iterator(root_);
    }

    template <typename T>
    typename LinkedBinaryTree<T>::Iterator LinkedBinaryTree<T>::end()
    {
        return Iterator();
    }

    template <typename T>
    typename LinkedBinaryTree<T>::Iterator LinkedBinaryTree<T>::end() const
    {
        return Iterator();
    }

    template <typename T>
    void LinkedBinaryTree<T>::print(const int& type)
    {
        auto l = Iterator(root_, type);
        auto r = Iterator(type);
        for (; l != r; ++l)
        {
            std::cout << static_cast<tree_node*>(l)->value << ' ';
        }
        std::cout << std::endl;
    }

    template <typename T>
    void LinkedBinaryTree<T>::unite(const T& value, LinkedBinaryTree& left, LinkedBinaryTree& right)
    {
        clear(root_);
        root_ = new tree_node(value);
        size_ = left.size_ + right.size_ + 1;
        build(root_->left, left);
        build(root_->right, right);
    }

    template <typename T>
    bool LinkedBinaryTree<T>::empty(tree_node*& node)
    {
        if (node == root_) { return size_ == 0; }
        auto count = 0;
        level_traversal(node, count, it_task_.node, ii_task_.none, i_task_.none);
        return count == 0;
    }

    template <typename T>
    int LinkedBinaryTree<T>::size(tree_node*& node)
    {
        if (node == root_) { return size_; }
        auto count = 0;
        level_traversal(node, count, it_task_.node, ii_task_.none, i_task_.none);
        return count;
    }

    template <typename T>
    int LinkedBinaryTree<T>::height(tree_node*& node)
    {
        auto count = 0;
        level_traversal(node, count, it_task_.none, ii_task_.none, i_task_.height);
        return count;
    }

    template <typename T>
    int LinkedBinaryTree<T>::width(tree_node*& node)
    {
        auto count = 0;
        level_traversal(node, count, it_task_.none, ii_task_.width, i_task_.none);
        return count;
    }

    template <typename T>
    void LinkedBinaryTree<T>::clear(tree_node*& node)
    {
        level_traversal(node, size_, it_task_.clear, ii_task_.none, i_task_.none);
    }

    template <typename T>
    void LinkedBinaryTree<T>::build(tree_node*& node, tree_node* const& that)
    {
        clear(node);
        node = new tree_node(that->value, that->left, that->right);
        if (node->left != nullptr)
        {
            build(node->left, that->left);
        }
        if (node->right != nullptr)
        {
            build(node->right, that->right);
        }
    }

    template <typename T>
    void LinkedBinaryTree<T>::traversal(tree_node*& node, ttask& pre, ttask& in, ttask& post)
    {
        ArrayStack<std::pair<tree_node*, bool>> s;
        tree_node* current = node;
        do
        {
            while (current != nullptr)
            {
                s.push({current, true});
                pre(current);
                current = current->left;
            }
            while (!s.empty() && !s.top().second)
            {
                post(s.top().first);
                s.pop();
            }
            if (!s.empty() && s.top().second)
            {
                in(s.top().first);
                current = s.top().first->right;
                s.top().second = false;
            }
        }
        while (!s.empty());
    }

    template <typename T>
    void LinkedBinaryTree<T>::level_traversal(tree_node*& node, int& count, ittask& point, iitask& line, itask& plane)
    {
        if (node == nullptr) { return; }
        ArrayQueue<tree_node*> q;
        q.push_back(node);
        while (!q.empty())
        {
            plane(count);
            auto len = q.size();
            line(count, len);
            while ((len--) != 0)
            {
                tree_node* f = q.front();
                q.pop_front();
                if (f->left != nullptr) { q.push_back(f->left); }
                if (f->right != nullptr) { q.push_back(f->right); }
                point(count, f);
            }
        }
    }

    template <typename T>
    bool LinkedBinaryTree<T>::operator!=(const LinkedBinaryTree& right)
    {
        return !(*this == right);
    }

    template <typename T>
    bool LinkedBinaryTree<T>::operator==(const LinkedBinaryTree& right)
    {
        if (size_ != right.size_) { return false; }
        auto l_begin = begin(kPre);
        auto r_begin = right.begin(kPre);
        while (static_cast<tree_node*>(l_begin) != nullptr)
        {
            if (l_begin != r_begin) { return false; }
            ++l_begin;
            ++r_begin;
        }
        return true;
    }

    template <typename T>
    LinkedBinaryTree<T>& LinkedBinaryTree<T>::operator=(const LinkedBinaryTree& right)
    {
        this->size_ = right.size_;
        build(root_, right.root_);
        return *this;
    }

    template <typename T>
    LinkedBinaryTree<T>& LinkedBinaryTree<T>::operator=(LinkedBinaryTree&& right) noexcept
    {
        this->size_ = right.size_;
        this->root_ = right.root_;
        right.size_ = 0;
        right.root_ = nullptr;
        return *this;
    }

    template <typename T>
    void LinkedBinaryTree<T>::build(tree_node*& node, T that[], const int index)
    {
        if (index > size_) { return; }
        node = new tree_node(that[index - 1]);
        build(node->left, that, index << 1);
        build(node->right, that, index << 1 | 1);
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(): type_(kIn), cursor_(nullptr), position_(nullptr)
    {
        initialize();
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(const int& type): type_(type), cursor_(nullptr), position_(nullptr)
    {
        initialize();
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(tree_node* that): type_(kIn), cursor_(that), position_(that)
    {
        initialize();
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(tree_node* that, const int& type): type_(type), cursor_(that),
                                                                               position_(that)
    {
        initialize();
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(const tree_node* that): type_(kIn), cursor_(that), position_(that)
    {
        initialize();
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(const tree_node* that, const int& type): type_(type), cursor_(that),
                                                                                     position_(that)
    {
        initialize();
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(const Iterator& that)
    {
        *this = that;
    }

    template <typename T>
    LinkedBinaryTree<T>::Iterator::Iterator(Iterator&& that) noexcept
    {
        *this = std::move(that);
    }

    template <typename T>
    constexpr LinkedBinaryTree<T>::Iterator::operator pointer() const
    {
        return position_;
    }

    template <typename T>
    constexpr typename LinkedBinaryTree<T>::Iterator::tree_node& LinkedBinaryTree<T>::Iterator::operator*() const
    {
        return *position_;
    }

    template <typename T>
    constexpr typename LinkedBinaryTree<T>::Iterator::tree_node* LinkedBinaryTree<T>::Iterator::operator->() const
    {
        return &*position_;
    }

    template <typename T>
    typename LinkedBinaryTree<T>::Iterator& LinkedBinaryTree<T>::Iterator::operator++()
    {
        if (type_ == kLevel)
        {
            if (position_ == nullptr) { return *this; }
            while (!q_.empty())
            {
                auto len = q_.size();
                while ((len--) != 0)
                {
                    position_ = q_.front().first;
                    q_.pop_front();
                    if (position_->left != nullptr) { q_.push_back({position_->left, true}); }
                    if (position_->right != nullptr) { q_.push_back({position_->right, true}); }
                    return *this;
                }
            }
        }
        else
        {
            do
            {
                while (cursor_ != nullptr)
                {
                    q_.push_back({cursor_, true});
                    if (type_ == kPre) { position_ = cursor_; }
                    cursor_ = cursor_->left;
                    if (type_ == kPre) { return *this; }
                }
                while (!q_.empty() && !q_.back().second)
                {
                    if (type_ == kPost) { position_ = q_.back().first; }
                    q_.pop_back();
                    if (type_ == kPost) { return *this; }
                }
                if (!q_.empty() && q_.back().second)
                {
                    if (type_ == kIn) { position_ = q_.back().first; }
                    cursor_ = q_.back().first->right;
                    q_.back().second = false;
                    if (type_ == kIn) { return *this; }
                }
            }
            while (!q_.empty());
        }
        position_ = nullptr;
        return *this;
    }

    template <typename T>
    const typename LinkedBinaryTree<T>::Iterator LinkedBinaryTree<T>::Iterator::operator++(int)
    {
        Iterator old = *this;
        ++(*this);
        return old;
    }

    template <typename T>
    constexpr bool LinkedBinaryTree<T>::Iterator::operator!=(const Iterator& right) const
    {
        return position_ != right.position_;
    }

    template <typename T>
    constexpr bool LinkedBinaryTree<T>::Iterator::operator==(const Iterator& right) const
    {
        return position_ == right.position_;
    }

    template <typename T>
    typename LinkedBinaryTree<T>::Iterator& LinkedBinaryTree<T>::Iterator::operator=(const Iterator& right)
    {
        type_ = right.type_;
        cursor_ = right.cursor_;
        position_ = right.position_;
        q_ = right.q_;
        return *this;
    }

    template <typename T>
    typename LinkedBinaryTree<T>::Iterator& LinkedBinaryTree<T>::Iterator::operator=(Iterator&& right) noexcept
    {
        type_ = right.type_;
        cursor_ = right.cursor_;
        right.cursor_ = nullptr;
        position_ = right.position_;
        right.position_ = nullptr;
        q_ = std::move(right.q_);
        return *this;
    }

    template <typename T>
    void LinkedBinaryTree<T>::Iterator::initialize()
    {
        if (type_ == kLevel) { q_.push_back({position_, true}); }
        if (cursor_ != nullptr) { ++(*this); }
    }
} // namespace yxl

#endif // !LINKED_BINARY_TREE_H
