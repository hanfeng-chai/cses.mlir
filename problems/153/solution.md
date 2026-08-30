# 153 - Subtree Queries

## Problem / 题目

On a rooted tree with node values, process queries: change a node's value, or sum the values in a node's subtree.

在有点权的有根树上处理询问：修改某节点的值，或求某节点子树内的值之和。

## Idea / 思路

Flatten the tree with an **Euler tour**, recording an entry time $\text{tin}[u]$ and exit time $\text{tout}[u]$ for each node; a subtree occupies the contiguous index range $[\text{tin}[u], \text{tout}[u]]$. Place node values into a Fenwick tree indexed by entry time. A value update is a point update at $\text{tin}[s]$, and a subtree sum is a Fenwick range sum over $[\text{tin}[s], \text{tout}[s]]$.

用**欧拉序**把树拍平，记录每个节点的进入时间 $\text{tin}[u]$ 与离开时间 $\text{tout}[u]$；子树占据连续下标区间 $[\text{tin}[u], \text{tout}[u]]$。把点权放入按进入时间为下标的树状数组。修改值是 $\text{tin}[s]$ 处的单点更新，子树求和是树状数组在 $[\text{tin}[s], \text{tout}[s]]$ 上的区间和。

## Complexity / 复杂度

Each operation is $O(\log n)$.

每个操作 $O(\log n)$。
