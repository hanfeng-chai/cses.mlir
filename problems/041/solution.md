# 041 - Distinct Values Subsequences

## Problem / 题目

Count the number of (non-empty) subsequences in which all values are distinct, modulo $10^9 + 7$.

统计所有值互不相同的（非空）子序列的数量，对 $10^9 + 7$ 取模。

## Idea / 思路

Any set of positions with pairwise distinct values forms exactly one valid subsequence (just read them left to right), so order imposes no extra constraint. Therefore each distinct value can be independently skipped or represented by one of its $c$ occurrences — that is $c + 1$ choices. Multiplying over all distinct values gives $\prod (c_v + 1)$; subtract $1$ to exclude the empty subsequence.

任意一组值两两不同的位置恰好构成一个合法子序列（从左到右读即可），所以顺序不带来额外约束。因此每个不同的值都可以独立地"不选"或用它的 $c$ 个出现之一来代表——即 $c + 1$ 种选择。对所有不同值相乘得到 $\prod (c_v + 1)$；再减 $1$ 去掉空子序列。

## Complexity / 复杂度

Counting occurrences and multiplying is $O(n)$.

统计出现次数并相乘为 $O(n)$。
