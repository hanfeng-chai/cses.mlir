# 252 - One Bit Positions

## Problem / 题目
For each distance $k$ from $1$ to $n-1$, count the pairs of positions $i>j$ with $i-j=k$ that both hold a one-bit.

对每个距离 $k$（$1$ 到 $n-1$），统计满足 $i-j=k$ 且两处都是 1 的位置对数。

## Idea / 思路
The count for distance $k$ is $\sum_j b_j b_{j+k}$, the autocorrelation of the bit array. Computing the convolution of the array with its reverse via FFT yields all these correlation values at once: the count for distance $k$ is the coefficient at index $n-1-k$.

距离 $k$ 的计数为 $\sum_j b_j b_{j+k}$，即位数组的自相关。用 FFT 计算数组与其反转的卷积可一次得到所有相关值：距离 $k$ 的计数为下标 $n-1-k$ 处的系数。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
