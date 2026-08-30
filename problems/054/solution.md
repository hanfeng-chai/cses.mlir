# 054 - Subarray Sums II

## Problem / 题目

Count the subarrays whose sum is exactly $x$; values may be **negative**.

统计和恰好为 $x$ 的子数组数量；数值可能为**负**。

## Idea / 思路

A subarray sum equals $\text{prefix}[r] - \text{prefix}[l]$, so we need $\text{prefix}[r] - \text{prefix}[l] = x$. Sweep the prefix sums, and for each prefix $p$ add the number of earlier prefixes equal to $p - x$, kept in a hash map. With negatives the two-pointer trick no longer works, so the hash map is essential; a custom splitmix64 hash defeats CSES's anti-hash tests that would otherwise force $O(n^2)$.

子数组的和等于 $\text{prefix}[r] - \text{prefix}[l]$，所以需要 $\text{prefix}[r] - \text{prefix}[l] = x$。扫描前缀和，对每个前缀 $p$ 加上之前等于 $p - x$ 的前缀个数，用哈希表维护。有负数时双指针失效，因此哈希表是必需的；自定义的 splitmix64 哈希可击败 CSES 的 anti-hash 测试（否则会被卡成 $O(n^2)$）。

## Complexity / 复杂度

A single pass with $O(1)$ expected hash operations gives $O(n)$.

单次遍历配合 $O(1)$ 期望哈希操作，为 $O(n)$。
