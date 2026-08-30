# 066 - Book Shop

## Problem / 题目

There are $n$ books, each with a price and a page count. With a budget of $x$, buy a subset (each book at most once) maximizing the total number of pages.

有 $n$ 本书，每本有价格和页数。预算为 $x$，购买一个子集（每本至多买一次），使总页数最大。

## Idea / 思路

This is the classic 0/1 knapsack. Let $dp[p]$ be the maximum pages achievable with budget exactly $p$ available. For each book $i$ we update $dp[p] = \max(dp[p],\, dp[p - h_i] + s_i)$ iterating $p$ from $x$ **down to** $h_i$; the descending order guarantees each book is used at most once. The answer is $dp[x]$.

这是经典 0/1 背包。设 $dp[p]$ 为预算为 $p$ 时可获得的最大页数。对每本书 $i$，从 $x$ **递减到** $h_i$ 更新 $dp[p] = \max(dp[p],\, dp[p - h_i] + s_i)$；递减顺序保证每本书至多用一次。答案为 $dp[x]$。

## Complexity / 复杂度

The time is $O(nx)$.

时间为 $O(nx)$。
