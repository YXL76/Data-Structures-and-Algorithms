#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/03 15:48:11
 * \Description:
 */

#ifndef LINKED_BINARY_TREE_NODE_H
#define LINKED_BINARY_TREE_NODE_H

#include <iostream>

namespace yxl
{
	template <typename T>
	struct LinkedBinaryTreeNode final
	{
		T value;
		LinkedBinaryTreeNode *left, *right;

		LinkedBinaryTreeNode<T>();
		explicit LinkedBinaryTreeNode<T>(const T& value);
		LinkedBinaryTreeNode<T>(const T& value, LinkedBinaryTreeNode<T>* left, LinkedBinaryTreeNode<T>* right);

		friend std::ostream& operator<<(std::ostream& out, const LinkedBinaryTreeNode<T>& item);
		friend std::ostream& operator<<(std::ostream& out, const LinkedBinaryTreeNode<T>&& item);
	};

	template <typename T>
	LinkedBinaryTreeNode<T>::LinkedBinaryTreeNode(): value(T()), left(nullptr), right(nullptr)
	{
	}

	template <typename T>
	LinkedBinaryTreeNode<T>::LinkedBinaryTreeNode(const T& value): value(value), left(nullptr), right(nullptr)
	{
	}

	template <typename T>
	LinkedBinaryTreeNode<T>::LinkedBinaryTreeNode(const T& value, LinkedBinaryTreeNode<T>* left,
	                                              LinkedBinaryTreeNode<T>* right): value(value), left(left),
	                                                                               right(right)
	{
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const LinkedBinaryTreeNode<T>& item)
	{
		out << item.value << ' ';
		return out;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& out, const LinkedBinaryTreeNode<T>&& item)
	{
		out << item.value << ' ';
		return out;
	}
} // namespace yxl

#endif // !LINKED_BINARY_TREE_NODE_H
