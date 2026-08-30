# 068 - Counting Towers

## Problem / 题目

Count the towers of width $2$ and height $n$ that can be built from blocks of arbitrary integer size (each block has width $1$ or $2$). Towers that look different after mirroring or rotation are counted separately. Answer each query modulo $10^9+7$.

统计用任意整数尺寸的积木（每块宽 $1$ 或 $2$）搭出宽 $2$、高 $n$ 的塔的方案数。镜像或旋转后看起来不同的塔分别计数。每个询问对 $10^9+7$ 取模。

## Idea / 思路

Build the tower one unit of height at a time and track the top boundary in two states: **split** (the two top cells are separate width-$1$ blocks) or **merged** (one width-$2$ block on top). Adding a row gives the recurrence $a' = 4a + b$ and $b' = a + 2b$, where $a$ is the split count and $b$ the merged count, with $a_1 = b_1 = 1$. The answer for height $n$ is $a_n + b_n$. We precompute all values up to $10^6$ once and answer every query in $O(1)$.

逐层（每次加一个单位高度）搭塔，并用两种状态描述顶部边界：**分离**（顶部两格是两块独立的宽 $1$ 积木）或**合并**（顶部是一块宽 $2$ 积木）。加一行得到递推 $a' = 4a + b$、$b' = a + 2b$，其中 $a$ 是分离数、$b$ 是合并数，初值 $a_1 = b_1 = 1$。高度 $n$ 的答案为 $a_n + b_n$。我们一次性预处理到 $10^6$，每个询问 $O(1)$ 作答。

## Complexity / 复杂度

Precomputation is $O(\max n)$ and each of the $t$ queries is $O(1)$.

预处理为 $O(\max n)$，$t$ 个询问每个 $O(1)$。
