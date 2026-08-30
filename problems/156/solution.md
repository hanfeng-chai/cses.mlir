# 156 - Distinct Colors

## Problem / 题目

On a rooted tree where each node has a color, compute for each node the number of distinct colors in its subtree.

在每个节点有颜色的有根树上，计算每个节点子树内不同颜色的数量。

## Idea / 思路

Flatten the tree with an **Euler tour** so that each subtree is a contiguous range $[\text{tin}[u], \text{tout}[u]]$, and write the color of the node entering at each position into an array indexed **by Euler position** (not by node). Counting distinct colors in each range is then the classic offline distinct-values-in-range problem: sort the ranges by right end, sweep with a Fenwick tree that keeps a $1$ at each color's last occurrence, and read off each range's count.

用**欧拉序**把树拍平，使每个子树是连续区间 $[\text{tin}[u], \text{tout}[u]]$，并把每个位置进入的节点颜色写入一个**按欧拉位置**（而非按节点）索引的数组。统计每个区间的不同颜色数就化为经典的离线区间数颜色问题：按右端排序区间，用在每种颜色最后一次出现处保留 $1$ 的树状数组扫描，读出每个区间的计数。

## Complexity / 复杂度

Sorting plus Fenwick operations give $O(n\log n)$.

排序加树状数组操作为 $O(n\log n)$。
