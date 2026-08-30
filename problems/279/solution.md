# 279 - Number of Subset Xors

## Problem / 题目
Count the number of distinct values obtainable as a subset xor.

求子集异或可得到的不同值的个数。

## Idea / 思路
The set of achievable subset xors is exactly the linear span of the values over $\mathbb{F}_2$. If the linear basis has rank $r$, the span has $2^r$ elements, so the answer is $2^r$.

可达的子集异或集合恰为这些值在 $\mathbb{F}_2$ 上的线性张成。若线性基秩为 $r$，张成有 $2^r$ 个元素，故答案为 $2^r$。

## Complexity / 复杂度
$O(n\log V)$. $O(n\log V)$。
