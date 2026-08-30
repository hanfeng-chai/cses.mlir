# 166 - Divisor Analysis

## Problem / 题目
Given the prime factorization $n=\prod x_i^{k_i}$, output the number, sum, and product of divisors of $n$, all modulo $10^9+7$.

给定质因数分解 $n=\prod x_i^{k_i}$，输出 $n$ 的因子个数、因子和、因子积，均模 $10^9+7$。

## Idea / 思路
- Number of divisors: $\prod (k_i+1)$.
- Sum of divisors: $\prod \dfrac{x_i^{k_i+1}-1}{x_i-1}$ (modular inverse for the division).
- Product of divisors: $n^{D/2}$ where $D$ is the divisor count, i.e. $\prod x_i^{k_i D/2}$. Because the exponent is enormous, reduce it modulo $p-1$ (Fermat); compute $D$ modulo $2(p-1)$ so that the division by $2$ is exact, splitting into the cases "$D$ even" and "$D$ odd" (then every $k_i$ is even).

- 因子个数：$\prod (k_i+1)$。
- 因子和：$\prod \dfrac{x_i^{k_i+1}-1}{x_i-1}$（除法用模逆元）。
- 因子积：$n^{D/2}$，$D$ 为因子个数，即 $\prod x_i^{k_i D/2}$。指数极大，按费马小定理对 $p-1$ 取模；为使除以 $2$ 精确，对 $2(p-1)$ 计算 $D$，并分「$D$ 为偶」与「$D$ 为奇」（此时每个 $k_i$ 均为偶）两种情形。

## Complexity / 复杂度
$O(n\log p)$ for $n$ prime factors. $n$ 个质因子时 $O(n\log p)$。
