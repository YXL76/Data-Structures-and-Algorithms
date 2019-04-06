#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/03 15:48:11
 * \Description:
 */

#ifndef LINKED_BINARY_TREE_NODE_H
#define LINKED_BINARY_TREE_NODE_H

#include <iostream>
#include <utility>

namespace yxl
{
    template <typename T>
    struct LinkedBinaryTreeNode final
    {
        T value;
        LinkedBinaryTreeNode *left, *right;

        constexpr LinkedBinaryTreeNode();
        constexpr explicit LinkedBinaryTreeNode(T value);
        constexpr LinkedBinaryTreeNode(T value, LinkedBinaryTreeNode<T>* left, LinkedBinaryTreeNode<T>* right);

        template <typename Tt>
        friend std::ostream& operator<<(std::ostream& out, const LinkedBinaryTreeNode<Tt>& item);
        template <typename Tt>
        friend std::ostream& operator<<(std::ostream& out, LinkedBinaryTreeNode<Tt>*& item);
    };

    template <typename T>
    constexpr LinkedBinaryTreeNode<T>::LinkedBinaryTreeNode(): value(T()), left(nullptr), right(nullptr)
    {
    }

    template <typename T>
    constexpr LinkedBinaryTreeNode<T>::LinkedBinaryTreeNode(T value): value(std::move(value)), left(nullptr),
                                                                      right(nullptr)
    {
    }

    template <typename T>
    constexpr LinkedBinaryTreeNode<T>::LinkedBinaryTreeNode(T value, LinkedBinaryTreeNode<T>* left,
                                                            LinkedBinaryTreeNode<T>* right): value(std::move(value)),
                                                                                             left(left),
                                                                                             right(right)
    {
    }

    template <class K, class V>
    std::ostream& operator<<(std::ostream& out, const std::pair<K, V>& item)
    {
        out << item.first << ':' << item.second;
        return out;
    }

    template <class K, class V>
    std::ostream& operator<<(std::ostream& out, const std::pair<K, V>*& item)
    {
        out << item->first << ':' << item->second;
        return out;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const LinkedBinaryTreeNode<T>& item)
    {
        out << item.value;
        return out;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, LinkedBinaryTreeNode<T>*& item)
    {
        out << item->value;
        return out;
    }
} // namespace yxl

#endif // !LINKED_BINARY_TREE_NODE_H
