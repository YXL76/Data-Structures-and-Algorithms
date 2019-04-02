/**
 * \Author: YXL
 * \LastUpdated: 
 * \Description: 
 */

#pragma once

#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#define LSON  root << 1, l, mid
#define RSON  (root << 1) + 1, mid + 1, r
#include <array>

class yxlSegmentTree final
{
public:
	yxlSegmentTree();
	~yxlSegmentTree();

	void push_up(const int& root);
	void push_down(const int& root, const int& l, const int& r);
	void build(int root, int l, int r);
	void update(int root, int l, int r, const int& ll, const int& rr, const int& val);
	void query(int root, int l, int r, const int& ll, const int& rr);

private:
	std::array<int, kMaxN> val_{};
	std::array<int, kMaxN> tree_{};
} my_tree;

yxlSegmentTree::yxlSegmentTree()
= default;

yxlSegmentTree::~yxlSegmentTree()
= default;

void yxlSegmentTree::push_up(const int& root) { tree_[root] = std::min(tree_[root << 1], tree_[(root << 1) + 1]); }

void yxlSegmentTree::push_down(const int& root, const int& l, const int& r)
{
	if (!val_[root]) return;
	if (l != r)
	{
		val_[root << 1] = val_[root];
		val_[(root << 1) + 1] = val_[root];
		tree_[root << 1] = val_[root];
		tree_[(root << 1) + 1] = val_[root];
	}
	val_[root] = 0;
}

void yxlSegmentTree::build(const int root, const int l, const int r)
{
	const auto mid = (l + r) >> 1;
	if (l == r)
	{
		scanf("%d", &tree_[root]);
		return;
	}
	build(LSON);
	build(RSON);
	push_up(root);
}

void yxlSegmentTree::update(const int root, const int l, const int r, const int& ll, const int& rr, const int& val)
{
	push_down(root, l, r);
	const auto mid = (l + r) >> 1;
	if (ll <= l && r <= rr)
	{
		tree_[root] = val_[root] = val;
		return;
	}
	if (ll <= mid) update(LSON, ll, rr, val);
	if (mid < rr) update(RSON, ll, rr, val);
	push_up(root);
}

void yxlSegmentTree::query(const int root, const int l, const int r, const int& ll, const int& rr)
{
	push_down(root, l, r);
	const auto mid = (l + r) >> 1;
	if (ll <= l && r <= rr)
	{
		ans = std::min(ans, tree_[root]);
		return;
	}
	if (ll <= mid) query(LSON, ll, rr);
	if (mid < rr) query(RSON, ll, rr);
}


#endif // !SEGMENT_TREE_H
