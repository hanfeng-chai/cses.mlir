# 185 - Sum of Four Squares

## Problem / 题目
For each $n$ (with total $\sum n\le 10^7$), output four non-negative integers $a,b,c,d$ with $a^2+b^2+c^2+d^2=n$.

对每个 $n$（且总和 $\sum n\le 10^7$），输出四个非负整数 $a,b,c,d$ 使 $a^2+b^2+c^2+d^2=n$。

## Idea / 思路
Precompute, for every value up to $10^7$, one representation as a sum of two squares via a sieve over pairs $(i,j)$ with $i^2+j^2\le 10^7$. For a query, loop over $a$ and $b$ with $a^2+b^2\le n$ and check whether the remainder $n-a^2-b^2$ has a stored two-square representation. Because the total of all $n$ is bounded, the overall work over all queries is bounded too.

用对所有 $i^2+j^2\le 10^7$ 的筛预处理出每个不超过 $10^7$ 的值的一组「两平方和」表示。查询时枚举 $a,b$（$a^2+b^2\le n$），检查余数 $n-a^2-b^2$ 是否有存储的两平方和表示。由于所有 $n$ 的总和有界，所有查询的总工作量也有界。

## Multi-solution / 多解
Any four valid numbers are accepted, so a custom checker verifies $a,b,c,d\ge 0$ and $a^2+b^2+c^2+d^2=n$.

任意四个合法数均可接受，故自定义 checker 验证 $a,b,c,d\ge 0$ 且 $a^2+b^2+c^2+d^2=n$。

## Complexity / 复杂度
Sieve $O(N)$ with $N=10^7$; queries amortized $O(\sum n)$ overall. 筛 $O(N)$（$N=10^7$）；所有查询均摊 $O(\sum n)$。
