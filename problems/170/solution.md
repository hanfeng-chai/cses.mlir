# 170 - Binomial Coefficients

## Problem / 题目
Answer $n$ queries of $\binom{a}{b}\bmod(10^9+7)$.

回答 $n$ 个 $\binom{a}{b}\bmod(10^9+7)$ 的询问。

## Idea / 思路
Precompute factorials $f[i]$ and their modular inverses up to $10^6$ (compute $f[M]^{-1}$ by Fermat, then fill the rest with the recurrence $\text{invf}[i]=\text{invf}[i+1]\cdot(i+1)$). Each query is $\binom{a}{b}=f[a]\cdot\text{invf}[b]\cdot\text{invf}[a-b]$.

预处理阶乘 $f[i]$ 及其模逆元到 $10^6$（用费马算 $f[M]^{-1}$，再用递推 $\text{invf}[i]=\text{invf}[i+1]\cdot(i+1)$ 反推）。每个询问 $\binom{a}{b}=f[a]\cdot\text{invf}[b]\cdot\text{invf}[a-b]$。

## Complexity / 复杂度
$O(M)$ preprocessing, $O(1)$ per query. 预处理 $O(M)$，每询问 $O(1)$。
