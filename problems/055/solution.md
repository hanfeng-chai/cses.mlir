# 055 - Subarray Divisibility

## Problem / 题目

Count the subarrays whose sum is divisible by $n$ (the array length).

统计和能被 $n$（数组长度）整除的子数组数量。

## Idea / 思路

A subarray sum is divisible by $n$ exactly when its two bounding prefix sums are congruent modulo $n$. So compute prefix sums modulo $n$ (mapping negatives into $[0, n)$), keep a count of how many prefixes fall in each residue class, and for each new prefix add the current count of its residue before incrementing it. Start with residue $0$ counted once for the empty prefix.

子数组的和能被 $n$ 整除，当且仅当其两个边界前缀和模 $n$ 同余。于是计算前缀和模 $n$（把负数映射到 $[0, n)$），维护每个余数类出现的次数，对每个新前缀先加上其余数当前的计数再自增。初始把余数 $0$ 计一次（对应空前缀）。

## Complexity / 复杂度

A single pass with an array of size $n$ for residues gives $O(n)$.

单次遍历配合大小为 $n$ 的余数数组，为 $O(n)$。
