# 178 - Counting Necklaces

## Problem / 题目
Count the distinct necklaces of $n$ beads with $m$ colors, where rotations are considered identical, modulo $10^9+7$.

求 $n$ 颗珠子、$m$ 种颜色、旋转视为相同的不同项链数，模 $10^9+7$。

## Idea / 思路
By Burnside's lemma over the cyclic group of rotations, the count is $\dfrac{1}{n}\sum_{d\mid n}\varphi(n/d)\,m^{d}$. Enumerate divisors of $n$ in $O(\sqrt n)$, evaluate each Euler totient by factorization, and divide by $n$ with a modular inverse.

由旋转循环群上的 Burnside 引理，个数为 $\dfrac{1}{n}\sum_{d\mid n}\varphi(n/d)\,m^{d}$。$O(\sqrt n)$ 枚举 $n$ 的因子，对每个用分解求欧拉函数，最后乘 $n$ 的模逆元。

## Complexity / 复杂度
$O(\sqrt n\,(\log m+\sqrt n))$. $O(\sqrt n\,(\log m+\sqrt n))$。
