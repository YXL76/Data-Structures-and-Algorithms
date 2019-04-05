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
        using tree_node = LinkedBinaryTreeNode<T>;
        using traversal_task = BinaryTreeTask<LinkedBinaryTreeNode<T>*>;

        using ttask = std::function<void(tree_node*&)>;
        using itask = std::function<void(int&)>;
        using iitask = std::function<void(int&, const int&)>;
        using ittask = std::function<void(int&, tree_node*&)>;

        LinkedBinaryTree();
        explicit LinkedBinaryTree(const T& value);
        LinkedBinaryTree(T that[], const int& size);
        LinkedBinaryTree(const LinkedBinaryTree<T>& that);
        LinkedBinaryTree(LinkedBinaryTree<T>&& that) noexcept;
        ~LinkedBinaryTree() override;

        virtual bool empty() { return empty(root_); }
        virtual int size() { return size(root_); }
        int height() { return height(root_); }
        int width() { return width(root_); }
        void clear() { return clear(root_); }

        void print_in_pre_order();
        void print_in_in_order();
        void print_in_post_order();
        void print_in_level_order();

        tree_node* root() { return root_; }

        void remove_left_subtree();
        void remove_right_subtree();

        void unite(const T& value, LinkedBinaryTree& left, LinkedBinaryTree& right);

        void t_task(ttask& pre, ttask& in, ttask& post);
        void lt_task(int& count, ittask& point, iitask& line, itask& plane);

        LinkedBinaryTree& operator=(const LinkedBinaryTree& right);
        LinkedBinaryTree& operator=(LinkedBinaryTree&& right) noexcept;

    protected:
        int size_{0};
        tree_node* root_;

        typename traversal_task::TTask t_task_;
        typename traversal_task::ITask i_task_;
        typename traversal_task::IiTask ii_task_;
        typename traversal_task::ItTask it_task_;

        bool empty(tree_node*& node) override;
        int size(tree_node*& node) override;
        int height(tree_node*& node) override;
        int width(tree_node*& node) override;
        void clear(tree_node*& node) override;
        void build(tree_node*& node, tree_node* const& that) override;
        void traversal(tree_node*& node, ttask& pre, ttask& in, ttask& post) override;
        void level_traversal(tree_node*& node, int& count, ittask& point, iitask& line, itask& plane) override;

    private:
        void build(tree_node*& node, T that[], int index);
    };

    template <typename T>
    LinkedBinaryTree<T>::LinkedBinaryTree(): root_(nullptr)
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
    void LinkedBinaryTree<T>::print_in_pre_order()
    {
        traversal(root_, t_task_.print, t_task_.none, t_task_.none);
    }

    template <typename T>
    void LinkedBinaryTree<T>::print_in_in_order()
    {
        traversal(root_, t_task_.none, t_task_.print, t_task_.none);
    }

    template <typename T>
    void LinkedBinaryTree<T>::print_in_post_order()
    {
        traversal(root_, t_task_.none, t_task_.none, t_task_.print);
    }

    template <typename T>
    void LinkedBinaryTree<T>::print_in_level_order()
    {
        auto count = 0;
        level_traversal(root_, count, it_task_.node_with_print, ii_task_.none, i_task_.none);
    }

    template <typename T>
    void LinkedBinaryTree<T>::remove_left_subtree()
    {
        clear(root_->left);
        root_->left = nullptr;
    }

    template <typename T>
    void LinkedBinaryTree<T>::remove_right_subtree()
    {
        clear(root_->right);
        root_->right = nullptr;
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
    void LinkedBinaryTree<T>::t_task(ttask& pre, ttask& in, ttask& post)
    {
        traversal(root_, pre, in, post);
    }

    template <typename T>
    void LinkedBinaryTree<T>::lt_task(int& count, ittask& point, iitask& line, itask& plane)
    {
        level_traversal(count, point, line, plane);
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
    void LinkedBinaryTree<T>::build(tree_node*& node, T that[], const int index)
    {
        if (index > size_) { return; }
        node = new tree_node(that[index - 1]);
        build(node->left, that, index << 1);
        build(node->right, that, index << 1 | 1);
    }
} // namespace yxl

#endif // !LINKED_BINARY_TREE_H
