/**
 * \Author: YXL
 * \LastUpdated: 2018/03/04 11:21:10
 * \Description:
 */

#pragma once

#ifndef YXL_LIST_H
#define YXL_LIST_H

template <typename T>
class yxlList
{
public:
    yxlList() = default;
    virtual ~yxlList() = default;
    yxlList(yxlList<T>& that) noexcept = default;
    yxlList(yxlList<T>&& that) noexcept = default;

    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual int index_of(const T& value) const = 0;
    virtual void clear() = 0;
    virtual void erase(const int& index) = 0;
    virtual void insert(const int& index, const T& value) = 0;

    yxlList& operator=(const yxlList<T>& right) = default;
    yxlList& operator=(yxlList<T>&& right) noexcept = default ;
};

#endif // !YXL_LIST_H
