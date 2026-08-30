# 278 - Maximum Xor Subset

## Problem / 题目
Find the maximum xor achievable by any subset of the array.

求数组任意子集可达的最大异或值。

## Idea / 思路
Build a linear (xor) basis of the values by Gaussian elimination over $\mathbb{F}_2$. Then greedily combine basis vectors from the highest bit: include a basis vector whenever it increases the running result. The final value is the maximum subset xor.

用 $\mathbb{F}_2$ 上的高斯消元构造数值的线性（异或）基。再从最高位起贪心组合基向量：每当某基向量能增大当前结果就纳入。最终值即最大子集异或。

## Complexity / 复杂度
$O(n\log V)$. $O(n\log V)$。
