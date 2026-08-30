# 207 - Counting Patterns

## Problem / 题目
For each pattern, count how many times it occurs in the string ($n\le 10^5$, total pattern length $\le 5\cdot10^5$).

对每个模式串，统计它在文本串中出现的次数（$n\le 10^5$，模式串总长 $\le 5\cdot10^5$）。

## Idea / 思路
Build the suffix automaton and compute each state's endpos size: initialize $1$ for the states created when extending (clones get $0$), then add each state's count to its suffix link in order of decreasing length. Walking a pattern lands on a state whose endpos size is exactly its number of occurrences (or $0$ if the walk fails).

构造后缀自动机并计算每个状态的 endpos 大小：扩展时新建的状态初始化为 $1$（克隆为 $0$），再按长度递减把每个状态的计数加到其后缀链接上。沿模式串行走到达的状态的 endpos 大小即为出现次数（行走失败则为 $0$）。

## Complexity / 复杂度
$O(n+\sum|p_i|)$. $O(n+\sum|p_i|)$。
