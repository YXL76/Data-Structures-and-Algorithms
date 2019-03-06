/**
 * \Author: YXL
 * \LastUpdated: 2018/03/04 11:21:10
 * \description:
 */

#pragma once

#ifndef YXL_CHAIN_H
#define YXL_CHAIN_H

#include "yxlList.h"

template<typename T>
class yxlChain final : public yxlList<T>
{
public:
    explicit yxlChain() = default;
    explicit yxlChain(yxlList<T>& that);
    explicit yxlChain(yxlList<T>&& that);
    ~yxlChain() override = default;

    bool empty() const override;
    unsigned size() const override;
    int index_of(const T& element) const override;
    void clear() override;
    void erase(const unsigned& index) override;
    void insert(const unsigned& index, const T& element) override;

    yxlChain& operator=(const yxlChain& right) = default;
    yxlChain& operator=(yxlChain&& right) noexcept = default;

private:
    unsigned size_;
};

template <typename T>
bool yxlChain<T>::empty() const
{
}

template <typename T>
unsigned yxlChain<T>::size() const
{
}

template <typename T>
int yxlChain<T>::index_of(const T& element) const
{
}

template <typename T>
void yxlChain<T>::clear()
{
}

template <typename T>
void yxlChain<T>::erase(const unsigned& index)
{
}

template <typename T>
void yxlChain<T>::insert(const unsigned& index, const T& element)
{
}
#endif // !YXL_CHAIN_H
