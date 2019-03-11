/**
 * \Author: YXL
 * \LastUpdated: 2018/03/04 11:21:10
 * \description:
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
    yxlList(yxlList& that) noexcept = default;
    yxlList(yxlList&& that) noexcept = default;

    virtual bool empty() const = 0;
    virtual unsigned size() const = 0;
    virtual int index_of(const T& value) const = 0;
    virtual void clear() = 0;
    virtual void erase(const unsigned& index) = 0;
    virtual void insert(const unsigned& index, const T& value) = 0;

    yxlList& operator=(const yxlList& right) = default;
    yxlList& operator=(yxlList&& right) noexcept = default ;
};

#endif // !YXL_LIST_H
