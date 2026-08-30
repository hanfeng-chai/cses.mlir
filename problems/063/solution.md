# 063 - Coin Combinations II

## Problem / 题目

Count the number of **unordered** ways (combinations) to form the sum $x$ from the given coins, each usable unlimited times. Print the answer modulo $10^9+7$.

统计用给定硬币（每种可无限次使用）凑出金额 $x$ 的**无序**方案数（即组合数）。结果对 $10^9+7$ 取模。

## Idea / 思路

The only change from the ordered version is the loop order: iterate the **coins** in the outer loop and the sum in the inner loop. Processing one coin completely before moving to the next means each combination is built in a fixed coin order, so $2+3$ and $3+2$ collapse into a single combination. The recurrence is still $dp[s] \mathrel{+}= dp[s-c]$.

与有序版本唯一的区别是循环顺序：外层枚举**硬币**、内层枚举金额。在转到下一种硬币之前先把当前硬币处理完，意味着每个组合都以固定的硬币顺序构造，于是 $2+3$ 与 $3+2$ 合并为同一个组合。递推式仍是 $dp[s] \mathrel{+}= dp[s-c]$。

## Complexity / 复杂度

The double loop gives $O(nx)$.

双重循环为 $O(nx)$。
