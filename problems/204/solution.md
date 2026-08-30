# 204 - Required Substring

## Problem / 题目
Count the strings of length $n$ over the alphabet A–Z that contain a given pattern of length $m$ as a substring, modulo $10^9+7$.

统计长度为 $n$、字母表为 A–Z、且包含给定长度 $m$ 模式串作为子串的字符串数，模 $10^9+7$。

## Idea / 思路
Count the complement (strings that never contain the pattern) and subtract from $26^n$. Build the KMP automaton of the pattern: state $j$ is the current matched prefix length. Do a DP over positions and states $0..m-1$; any transition that would reach the full match (state $m$) is dropped, since those strings already contain the pattern. The complement is the sum of $dp[n][\cdot]$, and the answer is $26^n$ minus it.

用补集（永不含模式串的字符串）从 $26^n$ 中减去。构造模式串的 KMP 自动机：状态 $j$ 表示当前匹配前缀长度。在位置与状态 $0..m-1$ 上做 DP；任何会到达完全匹配（状态 $m$）的转移都舍弃，因为这些串已含模式串。补集为 $dp[n][\cdot]$ 之和，答案即 $26^n$ 减之。

## Complexity / 复杂度
$O(n\,m\,\Sigma)$ with $\Sigma=26$. $O(n\,m\,\Sigma)$，$\Sigma=26$。
