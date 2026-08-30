# 186 - Triangle Number Sums

## Problem / 题目
For each $n$ (up to $10^{12}$) output the smallest number of triangular numbers $T_k=k(k+1)/2$ that sum to $n$.

对每个 $n$（可达 $10^{12}$）输出和为 $n$ 的三角数 $T_k=k(k+1)/2$ 的最少个数。

## Idea / 思路
By Gauss's Eureka theorem every positive integer is a sum of at most three triangular numbers, so the answer is $1$, $2$, or $3$.
- It is $1$ iff $n$ itself is triangular, i.e. $8n+1$ is a perfect square.
- Otherwise it is $2$ iff $n=T_a+T_b$, which is equivalent to $4n+1$ being a sum of two squares (every prime $\equiv 3\pmod 4$ in $4n+1$ has an even exponent).
- Otherwise the answer is $3$.

由高斯「Eureka」定理，每个正整数都是至多三个三角数之和，故答案为 $1$、$2$ 或 $3$。
- 为 $1$ 当且仅当 $n$ 本身是三角数，即 $8n+1$ 为完全平方数。
- 否则为 $2$ 当且仅当 $n=T_a+T_b$，等价于 $4n+1$ 是两平方和（$4n+1$ 中每个 $\equiv 3\pmod 4$ 的质数指数为偶）。
- 否则答案为 $3$。

## Complexity / 复杂度
$O(\sqrt{n})$ per query to factorize $4n+1$. 每询问 $O(\sqrt{n})$ 用于分解 $4n+1$。
