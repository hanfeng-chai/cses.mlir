# 093 - Flight Discount

## Problem / 题目

Find the cheapest route from city $1$ to city $n$ in a directed weighted graph, where you may halve the price of exactly one edge (rounded down) at most once.

在一个有向带权图中求从城市 $1$ 到城市 $n$ 的最便宜路线，途中至多可把一条边的价格减半一次（向下取整）。

## Idea / 思路

Model a state as (city, coupon already used?), doubling the graph into two layers. Run Dijkstra over these states: a normal edge keeps the layer, while using the coupon on an edge of price $w$ moves from the "unused" layer to the "used" layer at cost $\lfloor w/2 \rfloor$. The answer is the minimum of reaching city $n$ in either layer.

把状态建模为（城市，是否已用优惠券），把图复制成两层。在这些状态上跑 Dijkstra：普通边保持所在层，而对价格 $w$ 的边使用优惠券则以 $\lfloor w/2 \rfloor$ 的代价从"未用"层转到"已用"层。答案是在两层中到达城市 $n$ 的最小值。

## Complexity / 复杂度

The state graph has $2n$ nodes and $2m$ edges, so Dijkstra is $O((n+m)\log n)$.

状态图有 $2n$ 个节点、$2m$ 条边，因此 Dijkstra 为 $O((n+m)\log n)$。
