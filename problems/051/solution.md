# 051 - Sum of Four Values

## Problem / 题目

Find four values at distinct positions whose sum is $x$ (print any valid quadruple), or `IMPOSSIBLE`.

找出位于不同位置、和为 $x$ 的四个值（输出任意一组），否则输出 `IMPOSSIBLE`。

## Idea / 思路

Iterate the second pair by its first index $i$. Just before using $i$, store every pair ending at index $i-1$ in a hash map keyed by the pair's sum. Then for each later index $k$ look up $x - a[i] - a[k]$; any stored pair has both indices $< i$, guaranteeing all four positions are distinct. Because any valid quadruple is accepted, a checker (`checker.cpp`) validates the four indices and their sum.

按第二对的第一个下标 $i$ 迭代。在使用 $i$ 之前，把所有以下标 $i-1$ 结尾的对按其和为键存入哈希表。然后对每个更靠后的下标 $k$ 查询 $x - a[i] - a[k]$；存储的对两个下标都 $< i$，从而保证四个位置互异。由于接受任意合法四元组，checker（`checker.cpp`）校验四个下标及其和。

## Complexity / 复杂度

Both the insertions and the lookups span $O(n^2)$ pairs with $O(1)$ hashing, so the time is $O(n^2)$.

插入与查询都涉及 $O(n^2)$ 个对、配合 $O(1)$ 哈希，因此时间为 $O(n^2)$。
