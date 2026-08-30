# 286 - And Subset Count

## Problem / 题目
For each $k=0,1,\dots,n$, count the non-empty subsets whose bitwise AND equals $k$, modulo $10^9+7$.

对每个 $k=0,1,\dots,n$，统计按位与恰为 $k$ 的非空子集数，模 $10^9+7$。

## Idea / 思路
Let $c(k)$ be the number of elements that are supermasks of $k$ (a supermask sum). Any non-empty subset of those has AND that is a supermask of $k$, giving $g(k)=2^{c(k)}-1$ subsets with AND $\supseteq k$. Recover the exact counts by superset Möbius inversion: $\text{exact}(k)=\sum_{m\supseteq k}(-1)^{|m|-|k|}g(m)$, computed with an SOS-style transform.

设 $c(k)$ 为是 $k$ 超掩码的元素数（超掩码和）。它们的任意非空子集的 AND 都是 $k$ 的超掩码，故 AND $\supseteq k$ 的子集数为 $g(k)=2^{c(k)}-1$。用超集莫比乌斯反演还原精确计数：$\text{exact}(k)=\sum_{m\supseteq k}(-1)^{|m|-|k|}g(m)$，以 SOS 式变换计算。

## Complexity / 复杂度
$O(V\log V)$ with $V$ the next power of two above $n$. $O(V\log V)$，$V$ 为大于 $n$ 的最小 2 的幂。
