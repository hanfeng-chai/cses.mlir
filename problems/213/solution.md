# 213 - Inverse Suffix Array

## Problem / 题目
Given a suffix array (a permutation of $1..n$), reconstruct any lowercase string with that suffix array, or print $-1$ if impossible ($n\le 10^5$).

给定一个后缀数组（$1..n$ 的排列），还原任意一个具有该后缀数组的小写字母串，无法实现则输出 $-1$（$n\le 10^5$）。

## Idea / 思路
Let $\text{rank}[p]$ be the position of suffix $p$ in the suffix array. Assign letters to suffixes in suffix-array order, starting from `a`. Two consecutive suffixes $sa[i-1],sa[i]$ can share the same letter iff the order of their following suffixes is already consistent, i.e. $\text{rank}$ of the next position of $sa[i-1]$ is smaller than that of $sa[i]$ (treating an out-of-range next suffix as the smallest); otherwise the letter must increase. If more than $26$ letters are needed the answer is $-1$.

设 $\text{rank}[p]$ 为后缀 $p$ 在后缀数组中的位置。按后缀数组顺序从 `a` 起给后缀分配字母。相邻两后缀 $sa[i-1],sa[i]$ 能用同一字母当且仅当它们后继后缀的顺序已一致，即 $sa[i-1]$ 下一位置的 $\text{rank}$ 小于 $sa[i]$ 的（越界的后继视为最小）；否则必须递增字母。若需超过 $26$ 个字母则输出 $-1$。

## Multi-solution / 多解
Many strings may share a suffix array, so a custom checker rebuilds the suffix array of the output and verifies it matches (or that both sides report $-1$).

多个串可能共享同一后缀数组，故自定义 checker 重建输出串的后缀数组并验证一致（或双方都判 $-1$）。

## Complexity / 复杂度
$O(n)$. $O(n)$。
