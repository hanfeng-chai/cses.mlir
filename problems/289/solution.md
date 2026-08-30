# 289 - Third Permutation

## Problem / 题目
Given permutations $a,b$ with $a_i\neq b_i$ everywhere, construct a permutation $c$ with $c_i\neq a_i$ and $c_i\neq b_i$ for all $i$ (or IMPOSSIBLE).

给定处处 $a_i\neq b_i$ 的排列 $a,b$，构造排列 $c$ 使处处 $c_i\neq a_i$ 且 $c_i\neq b_i$（或 IMPOSSIBLE）。

## Idea / 思路
This is completing the third row of a Latin rectangle, which is possible for all $n\ge 3$ and impossible only for $n=2$. Greedily assign each position a still-free symbol other than $a_i,b_i$: whenever at least three symbols remain, one is always valid. Only the last positions (when $\le 2$ symbols remain) may be blocked; fix them with a swap against an already-assigned position.

这是补全 Latin 矩形的第三行，对所有 $n\ge 3$ 可行，仅 $n=2$ 不可行。贪心地给每个位置分配一个不等于 $a_i,b_i$ 的空闲符号：剩余至少三个符号时总有合法者。仅末尾（剩余 $\le 2$ 个符号）可能受阻，用与已分配位置的一次交换修复。

## Multi-solution / 多解
Any valid $c$ is accepted; a custom checker verifies it is a permutation avoiding $a$ and $b$.

任意合法 $c$ 均可；checker 验证它是避开 $a,b$ 的排列。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
