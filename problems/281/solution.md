# 281 - All Subarray Xors

## Problem / 题目
Output all distinct values that occur as the xor of some subarray.

输出所有作为某子数组异或而出现的不同值。

## Idea / 思路
A subarray xor is $\text{px}[i]\oplus\text{px}[j]$. A value $v$ is achievable iff some pair of prefix xors xors to $v$. Take the frequency array of prefix xors, apply the fast Walsh–Hadamard transform, square it pointwise, and invert: the result counts ordered prefix-xor pairs for each $v$, so every $v$ with a positive count is achievable (with a small adjustment for $v=0$, which requires a repeated prefix xor).

子数组异或为 $\text{px}[i]\oplus\text{px}[j]$。值 $v$ 可达当且仅当某对前缀异或的异或为 $v$。取前缀异或的频次数组，做快速 Walsh–Hadamard 变换、逐点平方、再逆变换：结果给出每个 $v$ 的有序前缀异或对数，故计数为正的 $v$ 均可达（$v=0$ 需前缀异或有重复，单独调整）。

## Complexity / 复杂度
$O(V\log V)$ with $V=2^{20}$. $O(V\log V)$，$V=2^{20}$。
