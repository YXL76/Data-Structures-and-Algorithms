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
    class BinaryTreeTask final
    {
    public:
        BinaryTreeTask() = default;
        BinaryTreeTask(const BinaryTreeTask& that) = default;
        BinaryTreeTask(BinaryTreeTask&& that) noexcept = default;
        ~BinaryTreeTask() = default;

        struct TTask final
        {
            TTask() : t_task_(t_none_)
            {
            }

            void none() { t_task_ = t_none_; }
            void clear() { t_task_ = clear_; }
            void print() { t_task_ = print_; }
            void operator()(T& x) { t_task_(x); }

        private:
            std::function<void(T&)> t_none_ = [](T& /*x*/)
            {
            };
            std::function<void(T&)> clear_ = [](T& x)
            {
                delete x;
                x = nullptr;
            };
            std::function<void(T&)> print_ = [](T& x) { std::cout << x << ' '; };

            std::function<void(T&)> t_task_;
        };

        struct ITask final
        {
            ITask() : i_task_(i_none_)
            {
            }

            void none() { i_task_ = i_none_; }
            void height() { i_task_ = height_; }
            void operator()(int& x) const { i_task_(x); }

        private:
            std::function<void(int&)> i_none_ = [](int& /*x*/)
            {
            };
            std::function<void(int&)> height_ = [](int& x) { ++x; };

            std::function<void(int&)> i_task_;
        };

        struct IiTask final
        {
            IiTask() : ii_task_(ii_none_)
            {
            }

            void none() { ii_task_ = ii_none_; }
            void width() { ii_task_ = width_; }
            void operator()(int& x, const int& y) const { ii_task_(x, y); }

        private:
            std::function<void(int&, const int&)> ii_none_ = [](int& /*x*/, const int& /*y*/)
            {
            };
            std::function<void(int&, const int&)> width_ = [](int& x, const int& y) { if (x < y) { x = y; } };

            std::function<void(int&, const int&)> ii_task_;
        };


        struct ItTask final
        {
            ItTask(): it_task_(it_none_)
            {
            }

            void none() { it_task_ = it_none_; }
            void node() { it_task_ = node_; }
            void node_with_print() { it_task_ = node_with_print_; }

            void operator()(int& x, T& y) const { it_task_(x, y); }
        private:
            std::function<void(int&, T&)> it_none_ = [](int& /*x*/, T& /*y*/)
            {
            };
            std::function<void(int&, T&)> node_ = [](int& x, T& y) { ++x; };
            std::function<void(int&, T&)> node_with_print_ = [](int& x, T& y)
            {
                ++x;
                std::cout << y << ' ';
            };

            std::function<void(int&, T&)> it_task_;
        };

        BinaryTreeTask& operator=(const BinaryTreeTask& right) = default;
        BinaryTreeTask& operator=(BinaryTreeTask&& right) noexcept = default;
    };
} // namespace yxl

#endif // !BINARY_TREE_TASK_H
