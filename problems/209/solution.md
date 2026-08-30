# 209 - Distinct Substrings

## Problem / 题目
Count the number of distinct substrings of a string ($n\le 10^5$).

统计字符串的不同子串个数（$n\le 10^5$）。

## Idea / 思路
Build the suffix automaton. Each state $v$ represents exactly $\text{len}(v)-\text{len}(\text{link}(v))$ distinct substrings, so the answer is the sum of this quantity over all states except the initial one.

构造后缀自动机。每个状态 $v$ 恰好代表 $\text{len}(v)-\text{len}(\text{link}(v))$ 个不同子串，故答案为除初始状态外所有状态该量之和。

## Complexity / 复杂度
$O(n)$. $O(n)$。
