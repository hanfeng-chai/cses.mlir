# 271 - Hidden Permutation

## Problem / 题目
Recover a hidden permutation of $1..n$ ($n\le 1000$) using at most $10^4$ comparisons "is $a_i<a_j$?".

用至多 $10^4$ 次「$a_i<a_j$ 吗？」的比较，还原 $1..n$（$n\le 1000$）的隐藏排列。

## Idea / 思路
Sort the indices by their hidden values using merge sort, where each comparison is a query. Merge sort uses at most $n\lceil\log_2 n\rceil\approx 10^4$ comparisons, and caching repeated pairs keeps the count safely within the limit. The position of an index in the sorted order is its value.

用归并排序按隐藏值对下标排序，每次比较即一次询问。归并排序比较数至多 $n\lceil\log_2 n\rceil\approx 10^4$，缓存重复对可稳妥地控制在上限内。下标在排序中的位置即其值。

## Complexity / 复杂度
$O(n\log n)$ queries. $O(n\log n)$ 次询问。
