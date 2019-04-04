#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/04 12:07:00
 * \Description:
 */

#ifndef STRING_ALGORITHM
#define STRING_ALGORITHM

#include "../List/Array.h"

namespace yxl
{
    class KMP final
    {
    public:
        KMP() = default;
        template <class T>
        explicit KMP(T& pattern_string);

        void clear();
        template <class T>
        void initialize(T& pattern_string);
        template <typename T>
        int search(T& text_string);

    private:
        bool is_initialize_{false};
        int size_{0};
        int* next_{nullptr};
        char* string_{nullptr};

        template <class T>
        void check_type(T& pattern_string);
    };

    inline void KMP::clear()
    {
        is_initialize_ = false;
        size_ = 0;
        delete [] next_;
        next_ = nullptr;
        delete [] string_;
        string_ = nullptr;
    }

    template <typename T>
    KMP::KMP(T& pattern_string)
    {
        check_type(pattern_string);
        initialize(pattern_string);
        is_initialize_ = true;
    }

    template <typename T>
    void KMP::initialize(T& pattern_string)
    {
        check_type(pattern_string);
        if (is_initialize_) { clear(); }
        size_ = static_cast<int>(pattern_string.size());
        next_ = new int [size_];
        string_ = new char [size_];
        for (auto i = 0; i < size_; ++i) { string_[i] = pattern_string[i]; }
        next_[0] = -1;
        auto left = -1;
        auto right = 0;
        while (right < size_ - 1)
        {
            if (left == -1 || string_[left] == string_[right])
            {
                ++left;
                ++right;
                if (string_[left] != string_[right]) { next_[right] = left; }
                else { next_[right] = next_[left]; }
            }
            else { left = next_[left]; }
        }
        is_initialize_ = true;
    }

    template <typename T>
    int KMP::search(T& text_string)
    {
        check_type(text_string);
        auto index_pattern = 0;
        auto index_text = 0;
        const int text_size = text_string.size();
        while (index_text < text_size && index_pattern < size_)
        {
            if (index_pattern == -1 || text_string[index_text] == string_[index_pattern])
            {
                ++index_pattern;
                ++index_text;
            }
            else { index_pattern = next_[index_pattern]; }
        }
        if (index_pattern == size_) { return index_text - index_pattern; }
        return -1;
    }

    template <class T>
    void KMP::check_type(T& /*pattern_string*/)
    {
        static_assert(std::is_same<T, std::string>::value || std::is_same<T, Array<char>>::value,
            "the parameter type must be string or Array<char>");
    }
} // namespace yxl

#endif // !STRING_ALGORITHM
