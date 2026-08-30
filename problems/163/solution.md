# 163 - Counting Divisors

## Problem / 题目
For each of $n$ numbers $x$ (up to $10^6$), report the number of divisors of $x$.

对 $n$ 个数 $x$（不超过 $10^6$），分别求 $x$ 的因子个数。

## Idea / 思路
Precompute a divisor-count table with a harmonic sieve: for every $i$ from $1$ to $10^6$, add one to every multiple of $i$. Then each query is an $O(1)$ lookup.

用调和级数筛预处理因子个数表：对每个 $i$ 从 $1$ 到 $10^6$，给它的每个倍数加 $1$。之后每次询问 $O(1)$ 查表即可。

## Complexity / 复杂度
Sieve $O(M\log M)$ with $M=10^6$, then $O(1)$ per query. 预处理 $O(M\log M)$（$M=10^6$），每次询问 $O(1)$。
