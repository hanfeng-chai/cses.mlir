# 034 - Missing Coin Sum

## Problem / 题目

Given $n$ coins with positive integer values, find the smallest sum that **cannot** be formed using any subset of the coins.

给定 $n$ 枚正整数面值的硬币，求**无法**用任何硬币子集凑出的最小和。

## Idea / 思路

Sort the coins ascending and maintain `reach`, the largest value such that **every** sum in $[1, \text{reach}]$ is formable (initially $0$). Process coins in increasing order: if the next coin $c$ satisfies $c \le \text{reach}+1$, it bridges the gap and extends the formable range to $\text{reach}+c$; otherwise $\text{reach}+1$ can never be formed and is the answer. The key invariant is that a coin larger than $\text{reach}+1$ leaves a permanent hole at $\text{reach}+1$.

把硬币升序排序，维护 `reach`：使得 $[1, \text{reach}]$ 内**每个**和都能凑出的最大值（初始为 $0$）。按升序处理硬币：若下一枚硬币 $c$ 满足 $c \le \text{reach}+1$，它能接上缺口，把可凑范围扩展到 $\text{reach}+c$；否则 $\text{reach}+1$ 永远凑不出，即为答案。关键不变量是：一旦某枚硬币大于 $\text{reach}+1$，就在 $\text{reach}+1$ 处留下了永久的空缺。

## Complexity / 复杂度

Sorting dominates the single scan, so the time is $O(n \log n)$.

排序是单次扫描的主要开销，因此时间为 $O(n \log n)$。
