#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/02 22:30:00
 * \Description:
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

namespace yxl
{
    template <typename E, typename T>
    class BinaryTree
    {
    public:
        BinaryTree() = default;
        virtual ~BinaryTree() = default;
        BinaryTree(const BinaryTree& that) = default;
        BinaryTree(BinaryTree&& that) = default;

        virtual bool empty(T*& node) = 0;
        virtual int size(T*& node) = 0;
        virtual int height(T*& node) = 0;
        virtual int width(T*& node) = 0;
        virtual void clear(T*& node) = 0;
        virtual void build(const E& value) = 0;
        virtual void build(T*& node, T*& that) = 0;
        virtual void traversal(T*& node) = 0;
        virtual void level_traversal(T*& node, int& count) = 0;

        BinaryTree& operator=(const BinaryTree& right) = default;
        BinaryTree& operator=(BinaryTree&& right) noexcept = default ;
    };
} // namespace yxl

#endif // !BINARY_TREE_H
