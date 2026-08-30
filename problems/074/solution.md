# 074 - Removal Game

## Problem / 题目

Two players alternately remove either the first or last number of a list, adding it to their score. Both play optimally to maximize their own score. Find the first player's score.

两名玩家轮流从列表头部或尾部取走一个数加到自己分数上，双方都最优地最大化自己的分数。求先手的得分。

## Idea / 思路

Work with the **score difference** (current player minus opponent) on each subarray. Let $d[i..j]$ be the best difference the player to move can guarantee; then $d[i..j] = \max(a_i - d[i+1..j],\; a_j - d[i..j-1])$, because after taking an end the roles swap and the opponent's optimal difference is subtracted. We compute it by increasing interval length, storing only one rolling array of size $n$. If $S$ is the total sum and $d$ the difference over the whole list, the first player's score is $(S + d)/2$.

在每个子数组上处理**得分差**（当前玩家减对手）。设 $d[i..j]$ 为轮到的玩家能保证的最优差值，则 $d[i..j] = \max(a_i - d[i+1..j],\; a_j - d[i..j-1])$，因为取走一端后角色互换，要减去对手的最优差值。我们按区间长度递增计算，只用一个大小为 $n$ 的滚动数组。设总和为 $S$、整段的差值为 $d$，则先手得分为 $(S + d)/2$。

## Complexity / 复杂度

There are $O(n^2)$ interval states each computed in constant time, so the time is $O(n^2)$ with $O(n)$ memory.

共 $O(n^2)$ 个区间状态、每个常数时间，因此时间 $O(n^2)$、空间 $O(n)$。
