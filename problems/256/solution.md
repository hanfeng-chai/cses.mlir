# 256 - Parcel Delivery

## Problem / 题目
Send $k$ parcels from city $1$ to city $n$ over capacitated routes with per-parcel costs, minimizing the total cost (or $-1$ if impossible).

通过有容量、按件计费的路线把 $k$ 件包裹从城市 $1$ 送到城市 $n$，最小化总费用（不可行则 $-1$）。

## Idea / 思路
Model it as a minimum-cost flow: each route becomes an edge with the given capacity and unit cost. Send $k$ units of flow from $1$ to $n$ using successive shortest augmenting paths (SPFA by cost). If the maximum flow is below $k$ the answer is $-1$; otherwise it is the accumulated cost.

建模为最小费用流：每条路线对应一条带容量与单位费用的边。用连续最短增广路（按费用做 SPFA）从 $1$ 到 $n$ 送 $k$ 单位流。若最大流不足 $k$ 则答案为 $-1$；否则为累计费用。

## Complexity / 复杂度
$O(k\cdot VE)$. $O(k\cdot VE)$。
