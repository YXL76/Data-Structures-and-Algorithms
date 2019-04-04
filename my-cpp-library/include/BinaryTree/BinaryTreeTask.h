#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/03 16:16:16
 * \Description:
 */

#ifndef BINARY_TREE_TASK_H
#define BINARY_TREE_TASK_H

#include <iostream>
#include <functional>

namespace yxl
{
	template <typename T>
	class BinaryTreeTask final
	{
	public:
		BinaryTreeTask() = default;
		BinaryTreeTask(const BinaryTreeTask& that) = default;
		BinaryTreeTask(BinaryTreeTask&& that) = default;
		~BinaryTreeTask() = default;

		void none();
		void clear();
		void count();
		void print();
		void operator()(T& x);

		BinaryTreeTask& operator=(const BinaryTreeTask& right) = default;
		BinaryTreeTask& operator=(BinaryTreeTask&& right) noexcept = default;

	private:
		std::function<void(T&)> task_;

		std::function<void(T&)> none_ = [](T& /*x*/)
		{
		};
		std::function<void(T&)> clear_ = [](T& x)
		{
			delete x;
			x = nullptr;
		};
		std::function<void(T&)> print_ = [](T& x) { std::cout << x << ' '; };
	};

	template <typename T>
	void BinaryTreeTask<T>::none()
	{
		task_ = none_;
	}

	template <typename T>
	void BinaryTreeTask<T>::clear()
	{
		task_ = clear_;
	}

	template <typename T>
	void BinaryTreeTask<T>::print()
	{
		task_ = print_;
	}

	template <typename T>
	void BinaryTreeTask<T>::operator()(T& x)
	{
		task_(x);
	}
} // namespace yxl

#endif // !BINARY_TREE_TASK_H
