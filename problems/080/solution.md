# 080 - Counting Tilings

## Problem / 题目

Count the number of ways to fill an $n \times m$ grid (with $n \le 10$) completely using $1 \times 2$ and $2 \times 1$ dominoes. Print the answer modulo $10^9+7$.

统计用 $1 \times 2$ 与 $2 \times 1$ 的多米诺骨牌恰好铺满 $n \times m$ 网格（$n \le 10$）的方案数。结果对 $10^9+7$ 取模。

## Idea / 思路

Use a broken-profile DP, processing the grid column by column. The state is a bitmask of the $n$ rows indicating which cells of the **current** column are already filled by horizontal dominoes protruding from the previous column. To advance one column, recurse over its rows and for each still-empty cell either place a horizontal domino (which protrudes into the next column, setting a bit of the outgoing mask) or a vertical domino covering it and the next free row. After the last column the outgoing mask must be empty, so the answer is $dp[0]$.

使用断面（broken-profile）DP，逐列处理网格。状态是 $n$ 行的位掩码，表示**当前**列中哪些格子已被上一列伸出的横向骨牌填充。要推进一列，对其各行递归，对每个仍为空的格子，要么放一块横向骨牌（伸入下一列，置出向掩码的一位），要么放一块竖向骨牌盖住它和下一空行。处理完最后一列后出向掩码必须为空，故答案为 $dp[0]$。

## Complexity / 复杂度

There are $m$ columns and $2^n$ profile states, with the per-column fill exploring a Fibonacci-bounded number of choices, comfortably fast for $n \le 10$.

共 $m$ 列、$2^n$ 个断面状态，每列填充探索的选择数受斐波那契式上界限制，对 $n \le 10$ 足够快。
