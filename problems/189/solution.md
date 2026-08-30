# 189 - Candy Lottery

## Problem / 题目
Each of $n$ children gets an independent uniform integer in $[1,k]$. Print the expected maximum, rounded to six decimals.

$n$ 个小孩各自独立地取 $[1,k]$ 上的均匀整数。输出期望的最大值，保留六位小数。

## Idea / 思路
Use the tail-sum formula $E[\max]=\sum_{v=1}^{k}\Pr[\max\ge v]=\sum_{v=1}^{k}\Big(1-\big(\tfrac{v-1}{k}\big)^{n}\Big)$, since all children are below $v$ with probability $((v-1)/k)^n$.

用尾和公式 $E[\max]=\sum_{v=1}^{k}\Pr[\max\ge v]=\sum_{v=1}^{k}\Big(1-\big(\tfrac{v-1}{k}\big)^{n}\Big)$，因为所有小孩都小于 $v$ 的概率为 $((v-1)/k)^n$。

## Complexity / 复杂度
$O(k\log n)$. $O(k\log n)$。
