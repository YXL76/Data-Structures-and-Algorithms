#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/03/04 11:21:10
 * \Description:
 */

#ifndef LIST_H
#define LIST_H

namespace yxl
{
    template <typename T>
    class List
    {
    public:
        constexpr List() = default;
        virtual ~List() = default;
        constexpr List(const List<T>& that) = default;
        constexpr List(List<T>&& that) noexcept = default;

        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual int index_of(const T& value) const = 0;
        virtual void clear() = 0;
        virtual void erase(const int& index) = 0;
        virtual void insert(const int& index, const T& value) = 0;

        List& operator=(const List<T>& right) = default;
        List& operator=(List<T>&& right) noexcept = default ;
    };
} // namespace yxl

#endif // !LIST_H
