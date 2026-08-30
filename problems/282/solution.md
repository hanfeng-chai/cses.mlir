# 282 - Xor Pyramid Peak

## Problem / 题目
In a pyramid where each number is the xor of the two numbers below it, find the top number given the bottom row.

在「每个数是其下方两数异或」的金字塔中，给定底行求顶端数。

## Idea / 思路
The top equals $\bigoplus_i a_i$ over indices $i$ where $\binom{n-1}{i}$ is odd. By Lucas' theorem $\binom{n-1}{i}$ is odd exactly when $i$ is a submask of $n-1$, so xor those $a_i$.

顶端等于在 $\binom{n-1}{i}$ 为奇数的下标 $i$ 上的 $\bigoplus_i a_i$。由卢卡斯定理，$\binom{n-1}{i}$ 为奇当且仅当 $i$ 是 $n-1$ 的子掩码，故对这些 $a_i$ 异或。

## Complexity / 复杂度
$O(n)$. $O(n)$。
