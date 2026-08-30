# 333 - Counting Sequences

## Problem / 题目

Count the sequences of length $n$ over the alphabet $\{1,\dots,k\}$ in which *every* value from $1$ to $k$ appears at least once (i.e. surjective sequences), modulo $10^9+7$.

求长度为 $n$、元素取自 $\{1,\dots,k\}$ 的序列中，$1$ 到 $k$ 每个值都至少出现一次（即"满射"序列）的个数，对 $10^9+7$ 取模。

## Idea / 思路

This is the classic "onto functions" / "surjection" counting formula, proved by inclusion–exclusion. There are $k^n$ sequences in total, with no restriction. To force every value to appear, start from all $k^n$ sequences and subtract those that *miss* at least one value, correcting for over-subtraction:

$$\text{surj}(n,k)=\sum_{i=0}^{k}(-1)^i\binom{k}{i}(k-i)^n.$$

Why: for a fixed set of $i$ "forbidden" values, the number of sequences that avoid *at least* those $i$ values is $(k-i)^n$ (only the remaining $k-i$ letters may be used); by inclusion–exclusion over which subset of values is missing, the term for excluding exactly a given set of $i$ values gets sign $(-1)^i$, and there are $\binom{k}{i}$ such subsets, giving the formula above. This is equivalent to $k!\cdot S(n,k)$ where $S(n,k)$ is the Stirling number of the second kind, but the direct inclusion–exclusion sum is simplest to compute here.

The implementation precomputes factorials/inverse factorials up to $k$ for binomial coefficients, and uses fast exponentiation for each $(k-i)^n$ term.

这是经典的"满射函数"计数公式，用容斥原理证明。总共有 $k^n$ 个不加限制的序列。要强制每个值都出现，从全部 $k^n$ 个序列出发，减去"缺失至少一个值"的序列，再修正减多了的部分：

$$\text{surj}(n,k)=\sum_{i=0}^{k}(-1)^i\binom{k}{i}(k-i)^n。$$

原理：固定一组 $i$ 个被"禁止"的值，避开这 $i$ 个值（只用剩下 $k-i$ 个字母）的序列数是 $(k-i)^n$；按"缺失的值构成的子集"做容斥，恰好缺失某个大小为 $i$ 的子集对应的项符号为 $(-1)^i$，这样的子集共 $\binom{k}{i}$ 个，就得到上面的公式。这等价于 $k!\cdot S(n,k)$（$S(n,k)$ 为第二类斯特林数），但直接用这个容斥求和是最简单的计算方式。

实现中预处理阶乘/阶乘逆元到 $k$ 用于计算组合数，并用快速幂计算每一项 $(k-i)^n$。

## Complexity / 复杂度

$O(k\log n)$ time (the sum has $k+1$ terms, each needing one fast exponentiation), $O(k)$ memory for factorials. With $k\le n\le10^6$ this is at most about $10^6\times20\approx2\times10^7$ operations.

时间 $O(k\log n)$（求和共 $k+1$ 项，每项一次快速幂），空间 $O(k)$ 存阶乘。$k\le n\le10^6$ 时约 $10^6\times20\approx2\times10^7$ 次操作。
