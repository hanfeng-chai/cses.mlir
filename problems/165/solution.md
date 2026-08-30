# 165 - Sum of Divisors

## Problem / 题目
Compute $\sigma$-style sum $\sum_{d=1}^{n} d\cdot\lfloor n/d\rfloor \bmod (10^9+7)$, equal to the sum of divisors of all numbers $1..n$, for $n$ up to $10^{12}$.

计算 $\sum_{d=1}^{n} d\cdot\lfloor n/d\rfloor \bmod (10^9+7)$（等于 $1..n$ 所有数的因子和），其中 $n$ 可达 $10^{12}$。

## Idea / 思路
Use divisor-block decomposition: the value $q=\lfloor n/d\rfloor$ is constant over a maximal range $d\in[\ell,r]$ with $r=\lfloor n/q\rfloor$. On each block add $q\cdot\big(S(r)-S(\ell-1)\big)$ where $S(x)=x(x+1)/2$ is the sum of $1..x$ modulo $p$ (use the modular inverse of $2$). There are only $O(\sqrt n)$ blocks.

使用整除分块：$q=\lfloor n/d\rfloor$ 在极大区间 $d\in[\ell,r]$（$r=\lfloor n/q\rfloor$）上为常数。每块贡献 $q\cdot\big(S(r)-S(\ell-1)\big)$，其中 $S(x)=x(x+1)/2$ 是 $1..x$ 模 $p$ 的和（用 $2$ 的模逆元）。块数只有 $O(\sqrt n)$。

## Complexity / 复杂度
$O(\sqrt n)$. $O(\sqrt n)$。
