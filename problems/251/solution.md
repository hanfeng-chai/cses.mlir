# 251 - Apples and Bananas

## Problem / 题目
With apple and banana weights in $1..k$, count for each total weight $w$ from $2$ to $2k$ the number of (apple, banana) pairs summing to $w$.

苹果和香蕉的重量在 $1..k$ 之间，对每个总重 $w$（$2$ 到 $2k$）统计和为 $w$ 的（苹果, 香蕉）对数。

## Idea / 思路
Let $A_i$ and $B_i$ count apples and bananas of weight $i$. The answer for weight $w$ is $\sum_{i+j=w} A_i B_j$, the convolution of the two count arrays, computed with a fast Fourier transform. Each value is at most $n\cdot m$, well within double-precision FFT accuracy.

设 $A_i$、$B_i$ 为重量 $i$ 的苹果、香蕉数。重量 $w$ 的答案为 $\sum_{i+j=w} A_i B_j$，即两个计数数组的卷积，用快速傅里叶变换计算。每个值至多 $n\cdot m$，在双精度 FFT 精度范围内。

## Complexity / 复杂度
$O(k\log k)$. $O(k\log k)$。
