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
#include <iostream>
#include <functional>

namespace yxl
{
	template <typename T>
	class LinkedBinaryTree final : public BinaryTree
	{
	public:

		LinkedBinaryTree();
		LinkedBinaryTree(LinkedBinaryTree<T>& that);
		LinkedBinaryTree(LinkedBinaryTree<T>&& that) noexcept;
		~LinkedBinaryTree() override = default;

		bool empty() const override;
		int size() const override;
		void clear() override;
		void print_in_pre_order() override;
		void print_in_in_order() override;
		void print_in_post_order() override;

		LinkedBinaryTree& operator=(const LinkedBinaryTree& right);
		LinkedBinaryTree& operator=(LinkedBinaryTree&& right) noexcept;

	private:
		int size_{0};
		LinkedBinaryTreeNode<T>* root_;
		BinaryTreeTask<LinkedBinaryTreeNode<T>*> pre_task_;
		BinaryTreeTask<LinkedBinaryTreeNode<T>*> in_task_;
		BinaryTreeTask<LinkedBinaryTreeNode<T>*> post_task_;

		static void copy(LinkedBinaryTreeNode<T>* left, const LinkedBinaryTreeNode<T>* right);
		void traversal(LinkedBinaryTreeNode<T>* node);
	};

	template <typename T>
	LinkedBinaryTree<T>::LinkedBinaryTree(): root_(nullptr)
	{
	}

	template <typename T>
	LinkedBinaryTree<T>::LinkedBinaryTree(LinkedBinaryTree<T>& that)
	{
		*this = that;
	}

	template <typename T>
	LinkedBinaryTree<T>::LinkedBinaryTree(LinkedBinaryTree<T>&& that) noexcept
	{
		*this = that;
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
		pre_task_.none();
		in_task_.none();
		post_task_.clear();
		traversal(root_);
	}

	template <typename T>
	void LinkedBinaryTree<T>::print_in_pre_order()
	{
		pre_task_.print();
		in_task_.none();
		post_task_.none();
		traversal(root_);
	}

	template <typename T>
	void LinkedBinaryTree<T>::print_in_in_order()
	{
		pre_task_.none();
		in_task_.print();
		post_task_.none();
		traversal(root_);
	}

	template <typename T>
	void LinkedBinaryTree<T>::print_in_post_order()
	{
		pre_task_.none();
		in_task_.none();
		post_task_.print();
		traversal(root_);
	}

	template <typename T>
	LinkedBinaryTree<T>& LinkedBinaryTree<T>::operator=(const LinkedBinaryTree& right)
	{
		this->size_ = right.size_;
		this->root_ = new LinkedBinaryTreeNode<T>(right.root_->value);
		copy(this->root_, right.root_);
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
	void LinkedBinaryTree<T>::copy(LinkedBinaryTreeNode<T>* left, const LinkedBinaryTreeNode<T>* right)
	{
		if (right == nullptr) return;
		left->left = new LinkedBinaryTreeNode<T>(right->left->value);
		left->right = new LinkedBinaryTreeNode<T>(right->right->value);
		copy(left->left, right->left->value);
		copy(left->right, right->right->value);
	}

	template <typename T>
	void LinkedBinaryTree<T>::traversal(LinkedBinaryTreeNode<T>* node)
	{
		if (node == nullptr) { return; }
		pre_task_(node);
		traversal(node->left);
		in_task_(node);
		traversal(node->right);
		post_task_(node);
	}
} // namespace yxl

#endif // !LINKED_BINARY_TREE_H
