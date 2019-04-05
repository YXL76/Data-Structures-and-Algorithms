#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/05 15:32:45
 * \Description:
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <utility>

namespace yxl
{
    template <class K, class V>
    class Dictionary
    {
    public:
        Dictionary() = default;
        virtual ~Dictionary() = default;
        Dictionary(const Dictionary<K, V>& that) = default;
        Dictionary(Dictionary<K, V>&& that) noexcept = default;

        virtual bool empty() = 0;
        virtual int size() = 0;
        virtual void erase(const K& key) = 0;
        virtual void insert(const std::pair<const K, V>& element) = 0;
        virtual std::pair<const K, V>* find(const K& key) const = 0;

        Dictionary& operator=(const Dictionary<K, V>& right) = default;
        Dictionary& operator=(Dictionary<K, V>&& right) noexcept = default;
    };
}

#endif // !DICTIONARY_H
