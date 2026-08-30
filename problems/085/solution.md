# 085 - Building Roads

## Problem / 题目

Given $n$ cities and $m$ existing roads, add the minimum number of new roads so that every city is reachable from every other, and output which roads to build.

给定 $n$ 座城市和 $m$ 条已有道路，添加最少的新道路使任意两城互达，并输出要修建的道路。

## Idea / 思路

Use a disjoint-set union (DSU) to find the connected components formed by the existing roads. If there are $k$ components, we need exactly $k-1$ new roads to merge them into one. Pick any representative city from each component and connect the first representative to each of the others. Any valid linking works, so a problem-specific checker (`checker.cpp`) accepts the output if it uses $k-1$ roads and leaves the graph connected.

用并查集（DSU）求出已有道路形成的连通分量。若有 $k$ 个分量，则恰好需要 $k-1$ 条新道路把它们并成一个。从每个分量取一个代表城市，把第一个代表与其余每个代表相连即可。任意合法的连接方式都行，故题目专用 checker（`checker.cpp`）在输出用了 $k-1$ 条道路且使图连通时判正确。

## Complexity / 复杂度

DSU operations are almost constant (inverse-Ackermann), so the time is $O((n+m)\,\alpha)$.

并查集操作几乎是常数（反阿克曼函数），因此时间为 $O((n+m)\,\alpha)$。
