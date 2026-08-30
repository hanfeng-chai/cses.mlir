# 317 - Bus Companies

## Problem / 题目
Each company lets you travel between any two of its cities for a fixed ticket price. Find the cheapest cost from city $1$ to every city.

每家公司可让你在其任意两座城市间以固定票价通行。求从城市 $1$ 到每座城市的最小花费。

## Idea / 思路
Model each company as an auxiliary node: add a zero-cost edge from each member city **to** the company node, and a cost-$c$ edge from the company node **to** each member city. Then a single ticket purchase costs $c$ when leaving the company node. Run Dijkstra from city $1$ over the $n+m$ nodes.

把每家公司建为辅助点：每座成员城市**到**公司点连费用 $0$ 的边，公司点**到**每座成员城市连费用 $c$ 的边；离开公司点即支付一次票价 $c$。在 $n+m$ 个点上从城市 $1$ 跑 Dijkstra。

## Complexity / 复杂度
$O((n+m+\textstyle\sum k)\log n)$. $O((n+m+\sum k)\log n)$。
