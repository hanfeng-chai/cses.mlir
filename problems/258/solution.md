# 258 - Distinct Routes II

## Problem / 题目
Find $k$ routes from room $1$ to room $n$, each teleporter usable at most once across all routes, minimizing the total number of teleporter uses (or $-1$ if impossible). Output the routes.

求从房间 $1$ 到房间 $n$ 的 $k$ 条路线，每个传送器在所有路线中至多用一次，最小化传送器使用总次数（不可行则 $-1$）。输出路线。

## Idea / 思路
Model it as a minimum-cost flow with every teleporter an edge of capacity $1$ and cost $1$. Send $k$ units from $1$ to $n$ with successive shortest paths; the minimum cost equals the total number of edges used. If the maximum flow is below $k$ the answer is $-1$. Otherwise decompose the flow into $k$ paths by repeatedly walking from $1$ to $n$ along edges that still carry flow.

建模为最小费用流，每个传送器是容量 $1$、费用 $1$ 的边。用连续最短路从 $1$ 到 $n$ 送 $k$ 单位流；最小费用即所用边总数。若最大流不足 $k$ 则答案为 $-1$。否则反复从 $1$ 沿仍有流的边走到 $n$，把流分解为 $k$ 条路径。

## Multi-solution / 多解
Any valid set of routes is accepted, so a custom checker verifies the routes are edge-disjoint paths from $1$ to $n$ whose total length equals the optimum reported by the jury.

任意合法路线集均可接受，故自定义 checker 验证路线是从 $1$ 到 $n$ 的边不相交路径，且总长等于标程给出的最优值。

## Complexity / 复杂度
$O(k\cdot VE)$. $O(k\cdot VE)$。
