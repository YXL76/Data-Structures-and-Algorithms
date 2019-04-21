#pragma once

/**
 * \Author: YXL
 * \LastUpdated: 2018/04/05 20:14:45
 * \Description:
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../Dictionary/Dictionary.h"
#include "../BinaryTree/LinkedBinaryTree.h"
#include <utility>

namespace yxl
{
    template <class K, class V>
    class BinarySearchTree final : public Dictionary<K, V>,
                                   public LinkedBinaryTree<std::pair<const K, V>>
    {
    public:
        using v_type = std::pair<const K, V>;
        using parent = LinkedBinaryTree<v_type>;
        using tree_node = LinkedBinaryTreeNode<v_type>;

        constexpr BinarySearchTree() = default;
        constexpr BinarySearchTree(const BinarySearchTree<K, V>& that) = default;
        constexpr BinarySearchTree(BinarySearchTree<K, V>&& that) noexcept = default;
        ~BinarySearchTree() override = default;

        bool empty() override;
        int size() override;
        void erase(const K& key) override;
        void insert(const v_type& element) override;
        v_type* find(const K& key) const override;

        v_type& operator[] (const K& key);

        BinarySearchTree& operator=(const BinarySearchTree<K, V>& right) = default;
        BinarySearchTree& operator=(BinarySearchTree<K, V>&& right) noexcept = default;

    private:
        void unite(const v_type& value, typename LinkedBinaryTree<std::pair<const K, V>>::tree_node*& /*left*/,
                   typename LinkedBinaryTree<std::pair<const K, V>>::tree_node*& /*right*/)
        {
        }

        void build(typename LinkedBinaryTree<std::pair<const K, V>>::tree_node*& /*node*/,
                   typename LinkedBinaryTree<std::pair<const K, V>>::tree_node* const& /*that*/) override
        {
        }
    };

    template <class K, class V>
    bool BinarySearchTree<K, V>::empty()
    {
        return parent::empty();
    }

    template <class K, class V>
    int BinarySearchTree<K, V>::size()
    {
        return parent::size();
    }

    template <class K, class V>
    void BinarySearchTree<K, V>::erase(const K& key)
    {
        auto* tar = parent::root_;
        tree_node* par = nullptr;
        while (tar != nullptr && tar->value.first != key)
        {
            par = tar;
            if (key < tar->value.first) { tar = tar->left; }
            else { tar = tar->right; }
        }
        if (tar == nullptr) { return; }

        if (tar->left != nullptr && tar->right != nullptr)
        {
            tree_node *son = tar->left, *s_par = tar;
            while (son->right != nullptr)
            {
                s_par = son;
                son = son->right;
            }
            auto* q = new tree_node(son->value, tar->left, tar->right);
            if (par == nullptr) { parent::root_ = q; }
            else
            {
                if (tar == par->left) { par->left = q; }
                else { par->right = q; }
            }
            if (s_par == tar) { par = q; }
            else { par = s_par; }
            delete tar;
            tar = son;
        }
        tree_node* son;
        if (tar->left != nullptr) { son = tar->left; }
        else { son = tar->right; }
        if (tar == parent::root_) { parent::root_ = son; }
        else
        {
            if (tar == par->left) { par->left = son; }
            else { par->right = son; }
        }
        --parent::size_;
        delete tar;
    }

    template <class K, class V>
    void BinarySearchTree<K, V>::insert(const v_type& element)
    {
        const K& key = element.first;
        auto* tar = parent::root_;
        tree_node* par = nullptr;
        while (tar != nullptr)
        {
            par = tar;
            if (key < tar->value.first) { tar = tar->left; }
            else if (key > tar->value.first) { tar = tar->right; }
            else
            {
                tar->value.second = element.second;
                return;
            }
        }
        auto* new_node = new tree_node(element);
        if (parent::root_ != nullptr)
        {
            if (key < par->value.first) { par->left = new_node; }
            else { par->right = new_node; }
        }
        else { parent::root_ = new_node; }
        ++parent::size_;
    }

    template <class K, class V>
    std::pair<const K, V>* BinarySearchTree<K, V>::find(const K& key) const
    {
        tree_node* target = parent::root_;
        while (target != nullptr)
        {
            if (key < target->value.first) { target = target->left; }
            else if (key > target->value.first) { target = target->right; }
            else { return &target->value; }
        }
        return nullptr;
    }

    template <class K, class V>
    typename BinarySearchTree<K, V>::v_type& BinarySearchTree<K, V>::operator[](const K& key)
    {
        return &*find(key);
    }
} // namespace yxl

#endif // !BINARY_SEARCH_TREE_H
