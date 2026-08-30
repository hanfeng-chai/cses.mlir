# 138 - Movie Festival Queries

## Problem / 题目

Given $n$ movies with start/end times, for each query (arrival, leaving) report the maximum number of non-overlapping movies watchable entirely within that window.

给定 $n$ 部有开始/结束时间的电影，对每个询问（到达, 离开）报告该时间窗内能完整观看的不重叠电影的最大数。

## Idea / 思路

The greedy rule "always watch the movie with the earliest end among those starting now or later" is optimal. Precompute $go[t]$ = the smallest end time among movies starting at time $\ge t$; this is the end time after watching one movie when free at time $t$. Build **binary lifting** tables over $go$ so that $up[j][t]$ jumps over $2^j$ greedy movies. A query from arrival $a$ to leaving $b$ counts, via binary lifting, how many movies can be chained while every end stays $\le b$.

贪心规则"在开始时间 $\ge$ 当前的电影里总看结束最早的那部"是最优的。预处理 $go[t]$ = 开始时间 $\ge t$ 的电影中最小的结束时间；这是在时刻 $t$ 空闲时看一部后的结束时间。在 $go$ 上建**二进制提升**表，使 $up[j][t]$ 跳过 $2^j$ 部贪心电影。对从到达 $a$ 到离开 $b$ 的询问，用二进制提升统计在所有结束时间 $\le b$ 的前提下能连看多少部。

## Complexity / 复杂度

Preprocessing is $O(T\log T)$ over the time range $T$; each query is $O(\log T)$.

预处理为时间范围 $T$ 上的 $O(T\log T)$；每个询问 $O(\log T)$。
