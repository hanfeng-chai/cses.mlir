# 208 - Pattern Positions

## Problem / 题目
For each pattern, output the first (1-indexed) position where it occurs in the string, or $-1$ if it never occurs.

对每个模式串，输出它在文本串中首次出现的位置（1 起始），不出现则 $-1$。

## Idea / 思路
Build the suffix automaton and store for each state the end index of its first occurrence (`firstpos`): set it to the current length when a state is created, and copy it from the original when cloning. Walking a pattern of length $\ell$ to a state $v$ gives a first start position $\text{firstpos}[v]-\ell+2$ (1-indexed); a failed walk gives $-1$.

构造后缀自动机，为每个状态记录首次出现的结束下标（`firstpos`）：新建状态时设为当前长度，克隆时从原状态复制。把长度为 $\ell$ 的模式串走到状态 $v$，首次起始位置为 $\text{firstpos}[v]-\ell+2$（1 起始）；行走失败则为 $-1$。

## Complexity / 复杂度
$O(n+\sum|p_i|)$. $O(n+\sum|p_i|)$。
