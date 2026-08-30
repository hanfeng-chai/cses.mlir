# 206 - Finding Patterns

## Problem / 题目
For each of $k$ patterns, report whether it occurs in the string ($n\le 10^5$, total pattern length $\le 5\cdot10^5$).

对每个（共 $k$ 个）模式串，判断它是否在文本串中出现（$n\le 10^5$，模式串总长 $\le 5\cdot10^5$）。

## Idea / 思路
Build the suffix automaton of the string. Every substring corresponds to a walk from the initial state, so a pattern occurs iff it can be fully traversed in the automaton. Each query just follows the transitions.

构造文本串的后缀自动机。每个子串对应从初始状态出发的一条行走，故模式串出现当且仅当能在自动机上被完整走完。每次查询沿转移行走即可。

## Complexity / 复杂度
$O(n+\sum|p_i|)$. $O(n+\sum|p_i|)$。
