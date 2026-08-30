# 095 - Flight Routes

## Problem / 题目

Find the prices of the $k$ cheapest routes from city $1$ to city $n$ in a directed weighted graph; a route may revisit cities, and routes with equal price are all counted.

在一个有向带权图中求从城市 $1$ 到城市 $n$ 的 $k$ 条最便宜路线的价格；路线可重复经过城市，价格相同的路线都算。

## Idea / 思路

This is the classic $k$-shortest-paths problem. Run a Dijkstra-like search but allow each city to be **finalized up to $k$ times**: keep a min-heap of (price, city), and each time we pop a city for the $i$-th time ($i \le k$) that price is its $i$-th shortest. We record the prices popped for city $n$; the first $k$ of them are the answer. A city is never pushed once it already has $k$ finalized prices, keeping the heap bounded.

这是经典的 $k$ 短路问题。做类似 Dijkstra 的搜索，但允许每座城市**最多被定型 $k$ 次**：维护 (价格, 城市) 的小根堆，每次第 $i$ 次（$i \le k$）弹出某城时，该价格就是它的第 $i$ 短。我们记录城市 $n$ 被弹出的价格，前 $k$ 个即为答案。某城已有 $k$ 个定型价格后就不再入堆，从而控制堆的规模。

## Complexity / 复杂度

Each edge is relaxed at most $k$ times, so the time is $O(k(n+m)\log)$ with small $k \le 10$.

每条边至多被松弛 $k$ 次，因此时间为 $O(k(n+m)\log)$，且 $k \le 10$ 很小。
