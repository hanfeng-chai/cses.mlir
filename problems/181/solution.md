# 181 - Throwing Dice

## Problem / 题目
Count the sequences of dice throws (each $1..6$) whose sum is exactly $n$, modulo $10^9+7$. $n$ can be up to $10^{18}$.

求点数和恰为 $n$ 的掷骰子序列数（每次 $1..6$），模 $10^9+7$。$n$ 可达 $10^{18}$。

## Idea / 思路
The counts satisfy $f(n)=\sum_{j=1}^{6} f(n-j)$ with $f(0)=1$. Encode this six-term linear recurrence as a $6\times 6$ companion matrix and raise it to the power $n$ with fast matrix exponentiation.

计数满足 $f(n)=\sum_{j=1}^{6} f(n-j)$，$f(0)=1$。把这个六项线性递推写成 $6\times 6$ 伴随矩阵，用矩阵快速幂求其 $n$ 次幂。

## Complexity / 复杂度
$O(6^3\log n)$. $O(6^3\log n)$。
