# 161 - Exponentiation

## Problem / 题目
For $n$ queries, compute $a^b \bmod (10^9+7)$.

对 $n$ 个询问，计算 $a^b \bmod (10^9+7)$。

## Idea / 思路
Binary (fast) exponentiation: square the base while scanning the bits of the exponent, multiplying into the result when a bit is set, all modulo the prime.

快速幂：扫描指数的二进制位，每步把底数平方，遇到为 1 的位就把它乘入答案，全程对该质数取模。

## Complexity / 复杂度
$O(\log b)$ per query. 每个询问 $O(\log b)$。
