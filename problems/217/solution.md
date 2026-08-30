# 217 - Substring Distribution

## Problem / 题目
For every length $1..n$, output the number of distinct substrings of that length ($n\le 10^5$).

对每个长度 $1..n$，输出该长度的不同子串个数（$n\le 10^5$）。

## Idea / 思路
Build the suffix automaton. Each state $v$ accounts for exactly one distinct substring of every length in the range $(\text{len}(\text{link}(v)),\ \text{len}(v)]$. Add $+1$ over that range with a difference array and take a prefix sum to obtain the count for each length.

构造后缀自动机。每个状态 $v$ 恰好为区间 $(\text{len}(\text{link}(v)),\ \text{len}(v)]$ 内的每个长度贡献一个不同子串。用差分数组在该区间加 $+1$，前缀和即得每个长度的子串数。

## Complexity / 复杂度
$O(n)$. $O(n)$。
