# 122 - Dynamic Range Minimum Queries

## Problem / 题目

Process queries on an array: update a single value, or ask the minimum of a range $[a,b]$.

在数组上处理询问：更新单个值，或询问区间 $[a,b]$ 的最小值。

## Idea / 思路

Use an iterative **segment tree** over the array, where each internal node stores the minimum of its two children. A point update changes a leaf and refreshes its ancestors; a range query walks the tree bottom-up, combining the $O(\log n)$ boundary nodes.

使用数组上的迭代式**线段树**，每个内部节点存其两个孩子的最小值。单点更新修改一个叶子并刷新祖先；区间询问自底向上遍历，合并 $O(\log n)$ 个边界节点。

## Complexity / 复杂度

Every operation is $O(\log n)$.

每个操作 $O(\log n)$。
