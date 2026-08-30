# 177 - Bracket Sequences II

## Problem / 题目
Count balanced bracket sequences of length $n$ that have a given prefix, modulo $10^9+7$.

求长度为 $n$、带有给定前缀的合法括号序列个数，模 $10^9+7$。

## Idea / 思路
Scan the prefix to get its current balance $b$ (open minus close); if it ever drops below $0$ the answer is $0$. We then need lattice paths of $L=n-k$ steps from height $b$ down to $0$ that never go negative. By the reflection principle this equals $\binom{L}{u}-\binom{L}{u-1}$ where $u=(L-b)/2$ is the number of up-steps; the count is $0$ unless $L-b$ is even and $b\le L$.

扫描前缀得到当前平衡度 $b$（左括号减右括号）；若中途 $<0$ 则答案为 $0$。随后需要从高度 $b$ 走 $L=n-k$ 步降到 $0$ 且不越过 $0$ 的格路。由反射原理其数目为 $\binom{L}{u}-\binom{L}{u-1}$，其中 $u=(L-b)/2$ 为上升步数；仅当 $L-b$ 为偶且 $b\le L$ 时非零。

## Complexity / 复杂度
$O(n)$. $O(n)$。
