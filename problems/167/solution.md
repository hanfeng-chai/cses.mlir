# 167 - Prime Multiples

## Problem / 题目
Given $k\le 20$ distinct primes, count integers in $[1,n]$ divisible by at least one of them ($n$ up to $10^{18}$).

给定 $k\le 20$ 个不同质数，统计 $[1,n]$ 中能被其中至少一个整除的整数个数（$n$ 可达 $10^{18}$）。

## Idea / 思路
Inclusion–exclusion over all non-empty subsets $S$: add $\lfloor n/\prod_{p\in S} p\rfloor$ with sign $(-1)^{|S|+1}$. The product can overflow, so accumulate it in $128$-bit and skip a subset as soon as the product exceeds $n$ (its contribution is $0$).

对所有非空子集 $S$ 做容斥：以符号 $(-1)^{|S|+1}$ 累加 $\lfloor n/\prod_{p\in S} p\rfloor$。乘积可能溢出，故用 $128$ 位累乘，一旦乘积超过 $n$ 立即跳过（其贡献为 $0$）。

## Complexity / 复杂度
$O(2^k\,k)$. $O(2^k\,k)$。
