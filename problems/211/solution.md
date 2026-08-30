# 211 - Repeating Substring

## Problem / 题目
Find a longest substring that occurs at least twice in the string, or $-1$ if none exists ($n\le 10^5$). Any longest one is accepted.

求一个在串中至少出现两次的最长子串，不存在则 $-1$（$n\le 10^5$）。任意最长解均可。

## Idea / 思路
Build the suffix automaton and compute endpos sizes. A substring repeats iff its state has endpos size $\ge 2$. Take the state of maximum length among those, and reconstruct the substring using a stored first-occurrence end index.

构造后缀自动机并计算 endpos 大小。一个子串重复出现当且仅当其状态的 endpos 大小 $\ge 2$。在这些状态中取长度最大者，用记录的首次出现结束下标还原子串。

## Multi-solution / 多解
Several longest repeating substrings may exist, so a custom checker verifies the output occurs at least twice and has the maximum possible length.

最长重复子串可能不唯一，故自定义 checker 验证输出至少出现两次且长度为最大值。

## Complexity / 复杂度
$O(n)$. $O(n)$。
