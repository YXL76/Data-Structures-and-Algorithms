/**
 * \Author: YXL
 * \LastUpdated: 2018/03/11 18:33:40
 * \description:
 */

#pragma once

#ifndef YXL_LINEAR_CONTAINER_H
#define YXL_LINEAR_CONTAINER_H

template<typename T>
class yxlLinearContainer
{
public:
    yxlLinearContainer() = default;
    virtual ~yxlLinearContainer() = default;
    yxlLinearContainer(yxlLinearContainer<T>& that) noexcept = default;
    yxlLinearContainer(yxlLinearContainer<T>&& that) noexcept = default;

    virtual bool empty() const = 0;
    virtual unsigned size() const = 0;
    virtual void clear() = 0;

    yxlLinearContainer& operator=(const yxlLinearContainer<T>& right) = default;
    yxlLinearContainer& operator=(yxlLinearContainer<T>&& right) noexcept = default;
};

#endif // !YXL_LINEAR_CONTAINER_H
