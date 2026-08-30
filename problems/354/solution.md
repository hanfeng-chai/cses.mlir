# 354 - Square Subsets

## Problem / 题目

Count the subsets of an array (including the empty subset) whose elements' product is a perfect square, modulo $10^9+7$.

求数组中元素乘积为完全平方数的子集个数（包括空子集，其乘积为 $1$），对 $10^9+7$ 取模。

## Idea / 思路

A product is a perfect square exactly when *every* prime appears with an even total exponent. So represent each $x_i$ not by its value but by a vector over $\mathbb{F}_2$: one coordinate per prime $\le5000$, set to $1$ if that prime's exponent in $x_i$ is *odd*, else $0$. The product of a subset is a square iff the **XOR** (= sum over $\mathbb{F}_2$) of its members' vectors is the all-zero vector.

This is the standard "count subsets XOR-ing to a target" linear-algebra problem. Build a linear basis of the $n$ vectors via Gaussian elimination over $\mathbb{F}_2$ (insert each vector, reducing it against the current basis; if it becomes zero it's linearly dependent, otherwise it becomes a new basis vector). If the basis ends up with rank $r$, the *kernel* of the map "subset $\to$ XOR of its vectors" has dimension $n-r$ — meaning exactly $2^{n-r}$ subsets map to any single value that's reachable at all, and the zero vector is always reachable (the empty subset reaches it, among others). So the answer is simply $2^{n-r}$.

Factor each $x_i\le5000$ with a precomputed smallest-prime-factor sieve to get its odd-exponent primes in $O(\log x_i)$, and store the resulting vector as a `bitset` (dimension = number of primes $\le5000$, about $669$) for fast XOR during Gaussian elimination.

*Sanity check:* $x=[2,2,3,6]$: vectors (on primes $2,3$) are $(1,0),(1,0),(0,1),(1,1)$; the basis is $\{(1,0),(0,1)\}$, rank $2$, so the answer is $2^{4-2}=4$ — matching the sample.

乘积是完全平方数，恰好等价于**每个**素数的总指数都是偶数。所以不用值本身表示 $x_i$，而是用一个 $\mathbb{F}_2$ 上的向量：每个 $\le5000$ 的素数占一个坐标，若该素数在 $x_i$ 中的指数是*奇数*就置 $1$，否则为 $0$。一个子集的乘积是完全平方数，等价于其成员向量的**异或**（$= \mathbb{F}_2$ 上的和）为全零向量。

这是"求异或到某目标值的子集个数"这一线性代数标准问题。对这 $n$ 个向量做 $\mathbb{F}_2$ 上的高斯消元，构造线性基（依次插入每个向量，与当前基做化简；若化简为零说明线性相关，否则成为新的基向量）。若最终基的秩为 $r$，则"子集 $\to$ 其向量异或"这个映射的**核**维数为 $n-r$——意味着对任何一个可达的目标值，恰有 $2^{n-r}$ 个子集映到它，而零向量总是可达的（空子集就映到它）。所以答案就是 $2^{n-r}$。

用预处理的最小素因子筛，对每个 $x_i\le5000$ 在 $O(\log x_i)$ 内求出指数为奇数的素数集合，把结果向量存成 `bitset`（维数=$\le5000$ 的素数个数，约 $669$），以便高斯消元时快速异或。

*验证：* $x=[2,2,3,6]$：（在素数 $2,3$ 上的）向量分别是 $(1,0),(1,0),(0,1),(1,1)$；基为 $\{(1,0),(0,1)\}$，秩 $2$，答案 $2^{4-2}=4$，与样例一致。

## Complexity / 复杂度

Sieving smallest prime factors up to $5000$ is $O(5000\log\log5000)$. Each of the $n$ vectors costs $O(\log x_i)$ to build and $O(\frac{\text{dim}}{64}\cdot\text{dim})$ to reduce against the basis; overall about $O(n\cdot\text{dim}^2/64)\approx3.5\times10^7$ for $n\le5000$.

筛 $5000$ 以内最小素因子需 $O(5000\log\log5000)$。每个向量构造 $O(\log x_i)$，与基做化简 $O(\frac{\text{dim}}{64}\cdot\text{dim})$；$n\le5000$ 时总体约 $O(n\cdot\text{dim}^2/64)\approx3.5\times10^7$。
