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
	class BinaryTree
	{
	public:
		BinaryTree() = default;
		virtual ~BinaryTree() = default;
		BinaryTree(BinaryTree& that) = default;
		BinaryTree(BinaryTree&& that) = default;

		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual void clear() = 0;
		virtual void print_in_pre_order() = 0;
		virtual void print_in_in_order() = 0;
		virtual void print_in_post_order() = 0;

		BinaryTree& operator=(const BinaryTree& right) = default;
		BinaryTree& operator=(BinaryTree&& right) noexcept = default ;
	};
} // namespace yxl

#endif // !BINARY_TREE_H
