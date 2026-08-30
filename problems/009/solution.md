# 009 - Bit Strings

## Problem / 题目

We must count the number of bit strings of length $n$, and print the result modulo $10^9+7$.

我们要统计长度为 $n$ 的比特串（0/1 串）的数量，并将结果对 $10^9+7$ 取模后输出。

## Idea / 思路

Each of the $n$ positions can independently be $0$ or $1$, so there are exactly $2^n$ bit strings. Since $n$ can be as large as $10^6$ and the result must be taken modulo $10^9+7$, we compute $2^n \bmod (10^9+7)$ using fast (binary) exponentiation, which squares the base while scanning the bits of the exponent.

$n$ 个位置中的每一个都可以独立地取 $0$ 或 $1$，所以恰好有 $2^n$ 个比特串。由于 $n$ 最大可达 $10^6$ 且结果要对 $10^9+7$ 取模，我们用快速幂（二进制幂）计算 $2^n \bmod (10^9+7)$：在扫描指数的二进制位的同时对底数反复平方。

## Why modular arithmetic / 为什么要取模

$2^n$ is astronomically large, so we never store it directly. Taking the modulo after every multiplication keeps all intermediate values within 64-bit range.

$2^n$ 大得天文数字，所以我们绝不直接存储它。每次乘法后立即取模，能让所有中间结果都保持在 64 位范围内。

## Complexity / 复杂度

Fast exponentiation runs in $O(\log n)$ time.

快速幂的时间复杂度是 $O(\log n)$。
