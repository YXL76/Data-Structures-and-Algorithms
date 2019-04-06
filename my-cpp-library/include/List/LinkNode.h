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

        constexpr LinkNode();
        constexpr explicit LinkNode(const T& value);
        constexpr LinkNode(const T& value, LinkNode* next);

        template <typename Tt>
        constexpr friend std::ostream& operator<<(std::ostream& out, const LinkNode<Tt>& item);
        template <typename Tt>
        constexpr friend std::ostream& operator<<(std::ostream& out, const LinkNode<Tt>* item);
    };

    template <typename T>
    constexpr LinkNode<T>::LinkNode(): value(T()), next(nullptr)
    {
    }

    template <typename T>
    constexpr LinkNode<T>::LinkNode(const T& value): value(value), next(nullptr)
    {
    }

    template <typename T>
    constexpr LinkNode<T>::LinkNode(const T& value, LinkNode* next): value(value), next(next)
    {
    }

    template <typename T>
    constexpr std::ostream& operator<<(std::ostream& out, const LinkNode<T>& item)
    {
        out << item.value;
        return out;
    }

    template <typename T>
    constexpr std::ostream& operator<<(std::ostream& out, const LinkNode<T>* item)
    {
        out << item->value;
        return out;
    }
} // namespace yxl

#endif // !LINK_NODE_H
