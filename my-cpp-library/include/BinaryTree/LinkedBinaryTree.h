#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/03 17:00:00
 * \Description:
 */

#ifndef LINKED_BINARY_TREE_H
#define LINKED_BINARY_TREE_H

#include "BinaryTree.h"
#include "BinaryTreeTask.h"
#include "LinkedBinaryTreeNode.h"
#include "../Queue/ArrayQueue.h"
#include <iostream>
#include <functional>

namespace yxl
{
    template <typename T>
    class LinkedBinaryTree final : public BinaryTree<T>
    {
    public:
        using tree_node = LinkedBinaryTreeNode<T>;
        using all_task = BinaryTreeTask<LinkedBinaryTreeNode<T>*>;

        LinkedBinaryTree();
        LinkedBinaryTree(const LinkedBinaryTree<T>& that);
        LinkedBinaryTree(LinkedBinaryTree<T>&& that) noexcept;
        ~LinkedBinaryTree() override;

        void build(T that[], const int& size) override;
        int height() override;
        bool empty() const override;
        int size() const override;
        void clear() override;
        void print_in_pre_order() override;
        void print_in_in_order() override;
        void print_in_post_order() override;
        void print_in_level_order() override;

        void build(LinkedBinaryTree& that);
        void unite(const T& value, LinkedBinaryTree& left, LinkedBinaryTree& right);
        void remove_left_subtree();
        void remove_right_subtree();

        LinkedBinaryTree& operator=(const LinkedBinaryTree& right);
        LinkedBinaryTree& operator=(LinkedBinaryTree&& right) noexcept;

    private:
        int size_{0};
        int count_{0};
        tree_node* root_;
        all_task pre_task_;
        all_task in_task_;
        all_task post_task_;

        int height(tree_node*& node);
        void clear(tree_node*& node);
        void build(tree_node*& node, const tree_node*& that);
        void build(tree_node*& node, T that[], int index);
        void traversal(tree_node*& node);
        void level_traversal(tree_node*& node);
    };

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(): root_(nullptr)
    {
    }

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(const LinkedBinaryTree<T>& that)
    {
        *this = that;
    }

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(LinkedBinaryTree<T>&& that) noexcept
    {
        *this = that;
    }

    template <typename T>
    LinkedBinaryTree<T>::~LinkedBinaryTree()
    {
        clear();
    }

    template <typename T>
    void LinkedBinaryTree<T>::build(T that[], const int& size)
    {
        clear(root_);
        size_ = size;
        build(root_, that, 1);
    }

    template <typename T>
    int LinkedBinaryTree<T>::height()
    {
        return height(root_);
    }

    template <typename T>
    bool LinkedBinaryTree<T>::empty() const
    {
        return size_ == 0;
    }

    template <typename T>
    int LinkedBinaryTree<T>::size() const
    {
        return size_;
    }

    template <typename T>
    void LinkedBinaryTree<T>::clear()
    {
        clear(root_);
        size_ = 0;
    }

    template <typename T>
    void LinkedBinaryTree<T>::print_in_pre_order()
    {
        pre_task_.print();
        in_task_.none();
        post_task_.none();
        count_ = 0;
        traversal(root_);
    }

    template <typename T>
    void LinkedBinaryTree<T>::print_in_in_order()
    {
        pre_task_.none();
        in_task_.print();
        post_task_.none();
        count_ = 0;
        traversal(root_);
    }

    template <typename T>
    void LinkedBinaryTree<T>::print_in_post_order()
    {
        pre_task_.none();
        in_task_.none();
        post_task_.print();
        count_ = 0;
        traversal(root_);
    }

    template <typename T>
    void LinkedBinaryTree<T>::print_in_level_order()
    {
        pre_task_.print();
        in_task_.none();
        post_task_.none();
        count_ = 0;
        level_traversal(root_);
    }

    template <typename T>
    void LinkedBinaryTree<T>::build(LinkedBinaryTree& that)
    {
        clear(root_);
        build(root_, that.root_);
        size_ = that.size_;
    }

    template <typename T>
    void LinkedBinaryTree<T>::unite(const T& value, LinkedBinaryTree& left, LinkedBinaryTree& right)
    {
        clear(root_);
        root_ = new tree_node(value);
        build(root_->left, left);
        build(root_->right, right);
        size_ = left.size_ + right.size_;
    }

    template <typename T>
    void LinkedBinaryTree<T>::remove_left_subtree()
    {
        LinkedBinaryTree left;
        left.root_ = root_->left;
        pre_task_.none();
        in_task_.none();
        post_task_.none();
        count_ = 0;
        traversal(root_->left);
        size_ -= count_;
        root_->left = nullptr;
    }

    template <typename T>
    void LinkedBinaryTree<T>::remove_right_subtree()
    {
        LinkedBinaryTree right;
        right.root_ = root_->right;
        pre_task_.none();
        in_task_.none();
        post_task_.none();
        count_ = 0;
        traversal(root_->right);
        size -= count_;
        root_->right = nullptr;
    }

    template <typename T>
    LinkedBinaryTree<T>& LinkedBinaryTree<T>::operator=(const LinkedBinaryTree& right)
    {
        this->size_ = right.size_;
        //build(root_, right.root_);
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
    int LinkedBinaryTree<T>::height(tree_node*& node)
    {
        if (node == nullptr) { return 0; }
        auto l_height = height(node->left);
        auto r_height = height(node->right);
        return l_height > r_height ? l_height : r_height;
    }

    template <typename T>
    void LinkedBinaryTree<T>::clear(tree_node*& node)
    {
        pre_task_.none();
        in_task_.none();
        post_task_.clear();
        count_ = 0;
        traversal(node);
    }

    template <typename T>
    void LinkedBinaryTree<T>::build(tree_node*& node, const tree_node*& that)
    {
        node = new tree_node(that->value, that->left, that->right);
        build(node->left, that->left);
        build(node->right, that->right);
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
    void LinkedBinaryTree<T>::traversal(tree_node*& node)
    {
        if (node == nullptr) { return; }
        ++count_;
        pre_task_(node);
        traversal(node->left);
        in_task_(node);
        traversal(node->right);
        post_task_(node);
    }

    template <typename T>
    void LinkedBinaryTree<T>::level_traversal(tree_node*& node)
    {
        ArrayQueue<tree_node*> q;
        tree_node* f = node;
        while (f != nullptr)
        {
            ++count_;
            pre_task_(f);
            if (f->left != nullptr) { q.push_back(f->left); }
            if (f->right != nullptr) { q.push_back(f->right); }
            if (q.empty()) { return; }
            f = q.front();
            q.pop();
        }
    }
} // namespace yxl

#endif // !LINKED_BINARY_TREE_H
