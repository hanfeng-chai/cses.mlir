# 168 - Counting Coprime Pairs

## Problem / 题目
Given an array of $n$ integers, count the pairs $(i,j)$, $i<j$, with $\gcd(x_i,x_j)=1$.

给定 $n$ 个整数，统计满足 $\gcd(x_i,x_j)=1$ 的下标对 $(i,j)$（$i<j$）的数量。

## Idea / 思路
Let $c_d$ be how many elements are divisible by $d$. By Möbius inversion the number of coprime pairs is $\sum_{d\ge 1}\mu(d)\binom{c_d}{2}$. Sieve the Möbius function up to the maximum value, compute every $c_d$ by summing frequencies over multiples of $d$, and accumulate.

设 $c_d$ 为可被 $d$ 整除的元素个数。由莫比乌斯反演，互质对数为 $\sum_{d\ge 1}\mu(d)\binom{c_d}{2}$。线性筛出莫比乌斯函数到最大值，对每个 $d$ 累加其倍数处的频次得到 $c_d$，再求和。

## Complexity / 复杂度
$O(M\log M)$ with $M$ the maximum value. $O(M\log M)$，$M$ 为最大值。
