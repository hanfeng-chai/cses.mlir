# 391 - Book Shop II

## Problem / 题目

There are $n$ book titles, each with a price $h_i$, page count $s_i$, and available copies $k_i$. Spending at most $x$ total, buying at most $k_i$ copies of book $i$, maximize the total number of pages.

有 $n$ 种书，每种价格 $h_i$、页数 $s_i$、库存 $k_i$ 本。花费总额不超过 $x$，第 $i$ 种最多买 $k_i$ 本，求能买到的最大总页数。

## Idea / 思路

This is the **bounded knapsack** problem (each item type has a limited quantity, unlike the unbounded "Book Shop" or the 0/1 "Book Shop II" variants seen elsewhere). The standard trick is **binary splitting**: represent buying anywhere from $0$ to $k_i$ copies of book $i$ as choosing a subset of $O(\log k_i)$ "bundles" of sizes $1,2,4,\dots$ (and a final leftover bundle), since any count from $0$ to $k_i$ can be written as a sum of a subset of these bundle sizes. Each bundle of size $c$ becomes a single ordinary 0/1-knapsack item with price $c\cdot h_i$ and value $c\cdot s_i$. Running the standard $O(\text{items}\times x)$ 0/1 knapsack DP on all bundles from all books then solves the bounded problem exactly.

With $n\le 100$ and $k_i\le 1000$, each book contributes $O(\log 1000)\approx 10$ bundles, so at most $\approx 1000$ items total — well inside the DP's budget.

这是**有限背包**问题（每种物品数量有限，区别于无限背包"Book Shop"或0/1背包版本）。标准技巧是**二进制拆分**：把购买第 $i$ 种书0到 $k_i$ 本的所有可能，表示为从 $O(\log k_i)$ 个大小为 $1,2,4,\dots$（以及最后一个剩余量）的"捆"中选一个子集——因为0到 $k_i$ 之间的任何数量都可以写成这些捆大小的某个子集之和。每个大小为 $c$ 的捆变成一个普通的0/1背包物品，价格 $c\cdot h_i$、价值 $c\cdot s_i$。对所有书的所有捆跑一次标准的 $O(\text{物品数}\times x)$ 0/1背包 DP，即可精确求解有限背包问题。

$n\le100$，$k_i\le1000$，每种书贡献约 $O(\log 1000)\approx10$ 个捆，总共约1000个物品，完全在DP的预算之内。

## Complexity / 复杂度

$O\big(n\log(\max k_i)\cdot x\big)\approx 1000\times 10^5=10^8$, fast enough for the time limit.

$O\big(n\log(\max k_i)\cdot x\big)\approx1000\times10^5=10^8$，时限内足够快。
