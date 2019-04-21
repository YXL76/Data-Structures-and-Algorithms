#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/20 20:49:08
 * \Description:
 */

#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include "../Heap/MinHeap.h"
#include "../BinaryTree/LinkedBinaryTree.h"
#include <string>
#include <utility>
#include <unordered_map>

namespace yxl
{
    class HuffmanTree final : public LinkedBinaryTree<char>
    {
    public:
        using binary_tree = LinkedBinaryTree<char>;
        using item_type = std::pair<int, binary_tree>;

        HuffmanTree() = default;;
        explicit HuffmanTree(const std::string& raw);
        HuffmanTree(const HuffmanTree& that);
        HuffmanTree(HuffmanTree&& that) noexcept;
        ~HuffmanTree() override = default;

        void print_table();
        void clear() override;
        std::string encode(const std::string& raw);
        std::string decode(const std::string& code) const;

        HuffmanTree& operator=(const HuffmanTree& right);
        HuffmanTree& operator=(HuffmanTree&& right) noexcept;

    private:
        std::unordered_map<char, std::string> table_;

        void build_tree(const std::string& raw);
        void build_table(tree_node* node, std::string code);
    };

    inline HuffmanTree::HuffmanTree(const std::string& raw)
    {
        build_tree(raw);
        build_table(root_, "");
    }

    inline HuffmanTree::HuffmanTree(const HuffmanTree& that)
    {
        *this = that;
    }

    inline HuffmanTree::HuffmanTree(HuffmanTree&& that) noexcept
    {
        *this = std::move(that);
    }

    inline void HuffmanTree::clear()
    {
        table_.clear();
        LinkedBinaryTree<char>::clear();
    }

    inline void HuffmanTree::print_table()
    {
        for (auto& i : table_)
        {
            std::cout << i.first << ':' << ' ' << i.second << std::endl;
        }
    }

    inline std::string HuffmanTree::encode(const std::string& raw)
    {
        std::string encoded;
        for (auto& i : raw)
        {
            encoded += table_[i];
        }
        return encoded;
    }

    inline std::string HuffmanTree::decode(const std::string& code) const
    {
        std::string raw;
        for (auto i = code.begin(); i < code.end(); ++i)
        {
            auto current = root_;
            while (current->left != nullptr)
            {
                if (*i == '0') { current = current->left; }
                else { current = current->right; }
                ++i;
            }
            --i;
            raw += current->value;
        }
        return raw;
    }

    inline HuffmanTree& HuffmanTree::operator=(const HuffmanTree& right)
    {
        table_ = right.table_;
        return *this;
    }

    inline HuffmanTree& HuffmanTree::operator=(HuffmanTree&& right) noexcept
    {
        table_ = std::move(right.table_);
        return *this;
    }

    inline void HuffmanTree::build_tree(const std::string& raw)
    {
        std::unordered_map<char, int> count;
        for (auto& i : raw) { ++count[i]; }
        MinHeap<item_type> heap;
        for (auto& i : count)
        {
            heap.push({i.second, binary_tree(i.first)});
        }
        for (auto i = 1; i < int(count.size()) && heap.size() > 1; ++i)
        {
            auto l = heap.top();
            heap.pop();
            auto r = heap.top();
            heap.pop();
            heap.push({l.first + r.first, binary_tree('\0', std::move(l.second), std::move(r.second))});
        }
        this->size_ = heap.top().second.size_;
        build(root_, heap.top().second.root_);
        heap.pop();
    }

    inline void HuffmanTree::build_table(tree_node* node, std::string code)
    {
        if (node->left == nullptr)
        {
            table_[node->value] = std::move(code);
            return;
        }
        build_table(node->left, code + '0');
        build_table(node->right, code + '1');
    }

    inline bool operator >(std::pair<int, LinkedBinaryTree<char>>& left, std::pair<int, LinkedBinaryTree<char>>& right)
    {
        return left.first > right.first;
    }

    inline bool operator <(std::pair<int, LinkedBinaryTree<char>>& left, std::pair<int, LinkedBinaryTree<char>>& right)
    {
        return left.first < right.first;
    }

    inline bool operator <=(std::pair<int, LinkedBinaryTree<char>>& left, std::pair<int, LinkedBinaryTree<char>>& right)
    {
        return left.first <= right.first;
    }

    inline bool operator >=(std::pair<int, LinkedBinaryTree<char>>& left, std::pair<int, LinkedBinaryTree<char>>& right)
    {
        return left.first <= right.first;
    }
}

#endif // !HUFFMAN_TREE
