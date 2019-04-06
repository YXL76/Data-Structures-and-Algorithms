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
    class BinaryTreeTask
    {
    public:
        constexpr BinaryTreeTask() = default;
        constexpr BinaryTreeTask(const BinaryTreeTask& that) = default;
        constexpr BinaryTreeTask(BinaryTreeTask&& that) noexcept = default;
        ~BinaryTreeTask() = default;

        struct TTask
        {
            std::function<void(T&)> none = [](T& /*x*/)
            {
            };
            std::function<void(T&)> clear = [](T& x)
            {
                delete x;
                x = nullptr;
            };
            std::function<void(T&)> print = [](T& x) { std::cout << x << ' '; };
        };

        struct ITask
        {
            std::function<void(int&)> none = [](int& /*x*/)
            {
            };
            std::function<void(int&)> height = [](int& x) { ++x; };
        };

        struct IiTask
        {
            std::function<void(int&, const int&)> none = [](int& /*x*/, const int& /*y*/)
            {
            };
            std::function<void(int&, const int&)> width = [](int& x, const int& y) { if (x < y) { x = y; } };
        };

        struct ItTask final
        {
            std::function<void(int&, T&)> none = [](int& /*x*/, T& /*y*/)
            {
            };
            std::function<void(int&, T&)> node = [](int& x, T& /*y*/) { ++x; };
            std::function<void(int&, T&)> clear = [](int& x, T& y)
            {
                --x;
                delete y;
                y = nullptr;
            };
            std::function<void(int&, T&)> node_with_print = [](int& x, T& y)
            {
                ++x;
                std::cout << y << ' ';
            };
        };

        BinaryTreeTask& operator=(const BinaryTreeTask& right) = default;
        BinaryTreeTask& operator=(BinaryTreeTask&& right) noexcept = default;
    };
} // namespace yxl

#endif // !BINARY_TREE_TASK_H
