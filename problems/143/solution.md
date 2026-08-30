# 143 - Missing Coin Sum Queries

## Problem / 题目

For each query, using only coins $a \dots b$, find the smallest sum that cannot be produced.

对每个询问，只用硬币 $a \dots b$，求无法凑出的最小总和。

## Idea / 思路

If the coins are processed in increasing value, the smallest unreachable sum grows as follows: keeping a reachable bound $\text{reach}$ (all sums $0..\text{reach}$ are producible), as long as there is a coin of value $\le \text{reach}+1$ we can extend, and the new bound becomes the total value of all coins $\le \text{reach}+1$. Because $\text{reach}$ at least doubles each productive step, only about $O(\log(\text{total}))$ steps are needed. Each step needs "sum of coins with index in $[a,b]$ and value $\le V$", answered with a **persistent segment tree over coin values** (version $i$ adds coin $i$, query is a difference of two versions). The answer is $\text{reach}+1$.

若按值递增处理硬币，最小不可达和如此增长：保持一个可达界 $\text{reach}$（所有 $0..\text{reach}$ 的和都可凑），只要存在值 $\le \text{reach}+1$ 的硬币就能扩展，新界变为所有值 $\le \text{reach}+1$ 的硬币总值。由于每次有效步 $\text{reach}$ 至少翻倍，只需约 $O(\log(\text{总和}))$ 步。每步需要"下标在 $[a,b]$ 且值 $\le V$ 的硬币总值"，用**按硬币值建的可持久化线段树**回答（版本 $i$ 加入硬币 $i$，查询是两版本之差）。答案为 $\text{reach}+1$。

## Complexity / 复杂度

Each query runs $O(\log(\text{total}))$ steps, each an $O(\log n)$ tree query.

每个询问 $O(\log(\text{总和}))$ 步，每步一次 $O(\log n)$ 的树查询。
