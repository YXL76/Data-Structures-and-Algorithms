#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/03 15:48:11
 * \Description:
 */

#ifndef LINK_NODE_H
#define LINK_NODE_H

namespace yxl
{
	template <typename T>
	struct LinkNode
	{
		T value;
		LinkNode* next;

		LinkNode();
		explicit LinkNode(const T& value);
		LinkNode(const T& value, LinkNode* next);
	};

	template <typename T>
	LinkNode<T>::LinkNode(): value(T()), next(nullptr)
	{
	}

	template <typename T>
	LinkNode<T>::LinkNode(const T& value): value(value), next(nullptr)
	{
	}

	template <typename T>
	LinkNode<T>::LinkNode(const T& value, LinkNode* next): value(value), next(next)
	{
	}
} // namespace yxl

#endif // !LINK_NODE_H
