# 105 - Road Construction

## Problem / 题目

Starting with $n$ isolated cities, process $m$ new roads one by one; after each road, report the current number of connected components and the size of the largest component.

从 $n$ 座孤立城市开始，逐条处理 $m$ 条新道路；每加一条后，报告当前连通分量数和最大分量的大小。

## Idea / 思路

Maintain a disjoint-set union with a size for each component. Start with $n$ components, each of size $1$, and track the running maximum size. For each new road, if its endpoints are already in the same component nothing changes; otherwise merge them, decrease the component count by one, add the sizes, and update the maximum. Print the two values after every road.

维护带大小的并查集。初始 $n$ 个分量、每个大小 $1$，并维护当前最大大小。对每条新道路，若两端已在同一分量则无变化；否则合并它们，分量数减一、大小相加、更新最大值。每条道路后输出这两个值。

## Complexity / 复杂度

Each road is an almost-constant DSU operation, so the total time is $O((n+m)\,\alpha)$.

每条道路是近乎常数的并查集操作，因此总时间为 $O((n+m)\,\alpha)$。
