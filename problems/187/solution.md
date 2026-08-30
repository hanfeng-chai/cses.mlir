# 187 - Dice Probability

## Problem / 题目
Throw a die $n$ times; print the probability that the sum lies in $[a,b]$, rounded to six decimals.

掷骰子 $n$ 次；输出点数和落在 $[a,b]$ 的概率，保留六位小数。

## Idea / 思路
Dynamic programming over the number of throws: $dp[s]$ is the probability the running sum equals $s$. Each die adds a face $1..6$ each with probability $1/6$. After $n$ throws sum the probabilities for $s\in[a,b]$.

按掷的次数做概率 DP：$dp[s]$ 为当前和等于 $s$ 的概率。每个骰子以 $1/6$ 概率加上点数 $1..6$。$n$ 次后累加 $s\in[a,b]$ 的概率。

## Complexity / 复杂度
$O(n\cdot 6n)$. $O(n\cdot 6n)$。
