# 169 - Next Prime

## Problem / 题目
For each given $n$ (up to about $10^{12}$), output the smallest prime strictly greater than $n$.

对每个给定的 $n$（可达约 $10^{12}$），输出严格大于 $n$ 的最小质数。

## Idea / 思路
Test successive candidates $n+1, n+2, \dots$ for primality with a deterministic Miller–Rabin test. Using the witness set $\{2,3,5,\dots,37\}$ is provably correct for all $n<3.3\cdot10^{24}$, far beyond the limit. Modular multiplication uses $128$-bit arithmetic to avoid overflow. Prime gaps are small, so few candidates are tested.

从 $n+1, n+2, \dots$ 逐个用确定性 Miller–Rabin 判素。取见证集 $\{2,3,5,\dots,37\}$ 对所有 $n<3.3\cdot10^{24}$ 都可证明正确，远超数据范围。模乘用 $128$ 位避免溢出。素数间隙很小，候选数很少。

## Complexity / 复杂度
$O(g\log^3 n)$ per query, $g$ the prime gap. 每个询问 $O(g\log^3 n)$，$g$ 为素数间隙。
