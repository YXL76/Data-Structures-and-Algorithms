#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/02 22:30:00
 * \Description:
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <functional>

namespace yxl
{
    template <typename T>
    class BinaryTree
    {
    public:
        using ttask = std::function<void(T*&)>;
        using itask = std::function<void(int&)>;
        using iitask = std::function<void(int&, const int&)>;
        using ittask = std::function<void(int&, T*&)>;

        BinaryTree() = default;
        virtual ~BinaryTree() = default;
        BinaryTree(const BinaryTree& that) = default;
        BinaryTree(BinaryTree&& that) noexcept = default;

        virtual bool empty(T*& node) = 0;
        virtual int size(T*& node) = 0;
        virtual int height(T*& node) = 0;
        virtual int width(T*& node) = 0;
        virtual void clear(T*& node) = 0;
        virtual void build(T*& node, T* const& that) = 0;
        virtual void traversal(T*& node, ttask& pre, ttask& in, ttask& post) = 0;
        virtual void level_traversal(T*& node, int& count, ittask& point, iitask& line, itask& plane) = 0;

        BinaryTree& operator=(const BinaryTree& right) = default;
        BinaryTree& operator=(BinaryTree&& right) noexcept = default ;
    };
} // namespace yxl

#endif // !BINARY_TREE_H
