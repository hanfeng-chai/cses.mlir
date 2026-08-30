# 392 - GCD Subsets

## Problem / 题目

Given an array of $n$ integers (each between $1$ and $n$), for every $k=1,\dots,n$ count the non-empty subsets whose gcd equals $k$, modulo $10^9+7$.

给定 $n$ 个整数（每个都在 $1$ 到 $n$ 之间），对每个 $k=1,\dots,n$，求元素的最大公约数恰好为 $k$ 的非空子集个数，对 $10^9+7$ 取模。

## Idea / 思路

Let $\mathrm{cnt}[g]$ be the number of array elements divisible by $g$ (computed by a divisor sieve: for each $g$, sum $\mathrm{cnt}$ of value-counts at multiples of $g$, $O(n\log n)$ total). Then
$$f[g] = 2^{\mathrm{cnt}[g]}-1$$
counts the non-empty subsets whose elements are *all* divisible by $g$ — i.e. subsets whose gcd is *some* multiple of $g$ (including $g$ itself).

To get the count with gcd **exactly** $g$, subtract off the subsets whose gcd is a larger multiple of $g$:
$$\mathrm{exact}[g] = f[g] - \sum_{\substack{m>g\\ g\mid m}} \mathrm{exact}[m].$$
Processing $g$ from $n$ down to $1$ (so every $\mathrm{exact}[m]$ needed is already known) computes all answers with one harmonic-sum sieve pass.

*Sanity check* on the sample ($n=5$, array $[5,4,4,2,3]$): $\mathrm{cnt}[1]=5,\mathrm{cnt}[2]=3$ (elements $4,4,2$), $\mathrm{cnt}[3]=1,\mathrm{cnt}[4]=2,\mathrm{cnt}[5]=1$. $f[5]=2^1-1=1=\mathrm{exact}[5]$ (no multiples of 5 beyond itself in range). $f[4]=2^2-1=3=\mathrm{exact}[4]$ similarly. $f[3]=2^1-1=1=\mathrm{exact}[3]$. $f[2]=2^3-1=7$; subtract $\mathrm{exact}[4]=3$ (multiples of 2 that are $>2$: just 4) $\Rightarrow \mathrm{exact}[2]=7-3=4$. $f[1]=2^5-1=31$; subtract $\mathrm{exact}[2]+\mathrm{exact}[3]+\mathrm{exact}[4]+\mathrm{exact}[5]=4+1+3+1=9 \Rightarrow \mathrm{exact}[1]=31-9=22$. Result: $22\ 4\ 1\ 3\ 1$ — exactly matches the expected output.

设 $\mathrm{cnt}[g]$ 为数组中能被 $g$ 整除的元素个数（用因数筛：对每个 $g$，把 $g$ 的所有倍数处的值计数累加，总复杂度 $O(n\log n)$）。则
$$f[g]=2^{\mathrm{cnt}[g]}-1$$
统计的是元素**全部**能被 $g$ 整除的非空子集——即最大公约数是 $g$ 的**某个倍数**（含 $g$ 本身）的子集个数。

要得到最大公约数**恰好**为 $g$ 的个数，需减去最大公约数是 $g$ 的更大倍数的部分：
$$\mathrm{exact}[g]=f[g]-\sum_{\substack{m>g\\ g\mid m}}\mathrm{exact}[m]。$$
按 $g$ 从 $n$ 递减到 $1$ 处理（这样用到的 $\mathrm{exact}[m]$ 都已算好），一次调和级数筛即可算出全部答案。

*样例验证*（$n=5$，数组 $[5,4,4,2,3]$）：$\mathrm{cnt}[1]=5,\mathrm{cnt}[2]=3$（元素 $4,4,2$），$\mathrm{cnt}[3]=1,\mathrm{cnt}[4]=2,\mathrm{cnt}[5]=1$。$f[5]=2^1-1=1=\mathrm{exact}[5]$。$f[4]=2^2-1=3=\mathrm{exact}[4]$。$f[3]=2^1-1=1=\mathrm{exact}[3]$。$f[2]=2^3-1=7$；减去 $\mathrm{exact}[4]=3$（大于2的2的倍数只有4）得 $\mathrm{exact}[2]=4$。$f[1]=2^5-1=31$；减去 $4+1+3+1=9$ 得 $\mathrm{exact}[1]=22$。结果 $22\ 4\ 1\ 3\ 1$，与期望输出完全一致。

## Complexity / 复杂度

Both the divisor-sieve for $\mathrm{cnt}$ and the multiple-sieve for $\mathrm{exact}$ are harmonic sums, $O(n\log n)$ total; modular exponentiation adds $O(n\log n)$ more. Fast for $n\le 2\times 10^5$.

求 $\mathrm{cnt}$ 的因数筛与求 $\mathrm{exact}$ 的倍数筛都是调和级数求和，总复杂度 $O(n\log n)$；模幂运算再加 $O(n\log n)$。$n\le2\times10^5$ 内很快。
