# 180 - Fibonacci Numbers

## Problem / 题目
Compute the $n$-th Fibonacci number modulo $10^9+7$ for $n$ up to $10^{18}$.

计算第 $n$ 个斐波那契数模 $10^9+7$，$n$ 可达 $10^{18}$。

## Idea / 思路
Use the fast-doubling identities
$$F(2k)=F(k)\big(2F(k+1)-F(k)\big),\qquad F(2k+1)=F(k)^2+F(k+1)^2,$$
recursing on the bits of $n$. This computes $F(n)$ and $F(n+1)$ together in logarithmic time.

使用快速倍增恒等式
$$F(2k)=F(k)\big(2F(k+1)-F(k)\big),\qquad F(2k+1)=F(k)^2+F(k+1)^2,$$
按 $n$ 的二进制位递归，对数时间内同时得到 $F(n)$ 与 $F(n+1)$。

## Complexity / 复杂度
$O(\log n)$. $O(\log n)$。
