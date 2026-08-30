# 172 - Distributing Apples

## Problem / 题目
Count the ways to distribute $m$ identical apples among $n$ children, modulo $10^9+7$.

求把 $m$ 个相同苹果分给 $n$ 个小孩的方案数，模 $10^9+7$。

## Idea / 思路
This is stars and bars: the number of non-negative integer solutions of $a_1+\dots+a_n=m$ is $\binom{n+m-1}{m}$. Precompute factorials up to $n+m$ and evaluate the binomial.

这是隔板法：$a_1+\dots+a_n=m$ 的非负整数解个数为 $\binom{n+m-1}{m}$。预处理阶乘到 $n+m$ 后直接求该二项式。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
