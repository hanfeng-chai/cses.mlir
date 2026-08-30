# 276 - Counting Bits

## Problem / 题目
Count the total number of one-bits in the binary representations of all integers from $1$ to $n$ ($n\le 10^{15}$).

统计 $1$ 到 $n$（$n\le 10^{15}$）所有整数二进制表示中 1 的总个数。

## Idea / 思路
Count each bit position independently. For bit $b$, the values toggle it in blocks of $2^{b+1}$: each full block contributes $2^b$ ones, plus the partial block contributes $\max(0,\,(n+1)\bmod 2^{b+1}-2^b)$. Sum over all bit positions.

按位独立统计。对第 $b$ 位，取值以 $2^{b+1}$ 为周期翻转：每个完整周期贡献 $2^b$ 个 1，末尾不完整部分贡献 $\max(0,\,(n+1)\bmod 2^{b+1}-2^b)$。对所有位求和。

## Complexity / 复杂度
$O(\log n)$. $O(\log n)$。
