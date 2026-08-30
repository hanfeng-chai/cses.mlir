# 398 - Stick Difference

## Problem / 题目

For each exact number of cuts $k=1,\dots,m$, split the given integer-length sticks into $n+k$ positive integer pieces so that the difference between the longest and shortest pieces is minimized.

对每个精确切割次数 $k=1,\dots,m$，把给定整数长度木棒切成 $n+k$ 段正整数长度的小棒，使最长与最短段之差最小。

## Idea / 思路

If original stick $i$ is split into $c_i\ge1$ pieces, the best internal split is as balanced as possible. Its pieces have lengths
$$\left\lfloor\frac{a_i}{c_i}\right\rfloor\quad\text{or}\quad\left\lceil\frac{a_i}{c_i}\right\rceil.$$
Thus an allocation $c_1+\dots+c_n=n+k$ has global range
$$\max_i\left\lceil\frac{a_i}{c_i}\right\rceil-
  \min_i\left\lfloor\frac{a_i}{c_i}\right\rfloor.$$
The challenge is to optimize both endpoints simultaneously for every $k$.

### Frontier 1: minimize the maximum / 前沿1：最小化最大段

Start with $c_i=1$. Repeatedly give the next cut to the stick with largest current
$$\left\lceil a_i/c_i\right\rceil.$$
This is the standard greedy for minimizing the maximum piece length: if the current largest ceiling is not split, no other cut can reduce that bottleneck. On ties, prefer the larger floor to obtain a canonical Pareto point.

After $j$ cuts record:
$$Y_j=\max_i\left\lceil a_i/c_i\right\rceil,$$
$$V_j=\min_i\left\lfloor a_i/c_i\right\rfloor.$$
A max-heap selects the next stick, while a multiset maintains the global minimum floor.

### Frontier 2: maximize the minimum / 前沿2：最大化最小段

Independently restart from $c_i=1$. If stick $i$ receives one more cut, its new floor becomes
$$\left\lfloor a_i/(c_i+1)\right\rfloor.$$
Always choose the stick with the largest such next floor. This postpones lowering the global minimum as much as possible. After $k$ cuts record the largest achievable minimum piece length $X_k$. Again use a max-heap for next-floor candidates and a multiset for the current global minimum.

### Combine the frontiers / 合并两条前沿

For fixed $k$, find the largest $p\le k$ such that
$$V_p\ge X_k.$$
The sequence $V_j$ is nonincreasing, so binary search applies.

- For allocations before or at $p$, the minimum can still be kept at the optimal value $X_k$ while using the remaining cuts. Since $Y_j$ decreases with $j$, the best candidate there is
  $$Y_p-X_k.$$
- Beyond $p$, the maximum-minimizing frontier has already dropped below $X_k$; its own realized ranges
  $$D_j=Y_j-V_j$$
  contain the relevant Pareto candidates. Take
  $$\min_{p<j\le k}D_j.$$

Build a range-minimum segment tree over $D_0,\dots,D_m$ to answer this second part. The minimum of the two candidates is the optimum for exactly $k$ cuts.

若原木棒 $i$ 被分成 $c_i\ge1$ 段，其内部最优切法必然尽量均匀，段长只有
$$\left\lfloor\frac{a_i}{c_i}\right\rfloor\quad\text{或}\quad\left\lceil\frac{a_i}{c_i}\right\rceil。$$
因此满足 $c_1+\dots+c_n=n+k$ 的分配，其全局极差为
$$\max_i\left\lceil\frac{a_i}{c_i}\right\rceil-
  \min_i\left\lfloor\frac{a_i}{c_i}\right\rfloor。$$
难点是同时优化两个端点，并求出每个 $k$。

从 $c_i=1$ 开始，反复把下一刀分配给当前
$$\left\lceil a_i/c_i\right\rceil$$
最大的木棒。这是最小化最大段长的标准贪心：若不切当前最大上取整值对应的木棒，切其他木棒无法降低瓶颈。每用 $j$ 刀记录最大段 $Y_j$ 与最小段 $V_j$。大顶堆选择下一根木棒，多重集合维护全局最小下取整值。

独立地重新从 $c_i=1$ 开始。若木棒 $i$ 再切一刀，其新最小段为
$$\left\lfloor a_i/(c_i+1)\right\rfloor。$$
每次选择该“下一最小段”最大的木棒，尽可能推迟全局最小值下降。用 $k$ 刀后记录可达到的最大最小段 $X_k$。

固定 $k$，找最大的 $p\le k$ 满足
$$V_p\ge X_k。$$
$V_j$ 单调不增，可二分。

- 在 $p$ 之前仍能让最小段保持最优值 $X_k$，且 $Y_j$ 随 $j$ 下降，所以最佳候选为 $Y_p-X_k$；
- 在 $p$ 之后，最大值前沿自身的极差
  $$D_j=Y_j-V_j$$
  给出剩余 Pareto 候选，查询
  $$\min_{p<j\le k}D_j。$$

对 $D_0,\dots,D_m$ 建区间最小线段树，两种候选的较小值就是恰好切 $k$ 刀的答案。

## Complexity / 复杂度

Both greedy frontiers take $O((n+m)\log n)$. Each answer uses binary search and one RMQ in $O(\log m)$, for total $O((n+m)\log(n+m))$ time and $O(n+m)$ memory.

两条贪心前沿共需 $O((n+m)\log n)$。每个答案用一次二分和一次 $O(\log m)$ RMQ，总时间 $O((n+m)\log(n+m))$，空间 $O(n+m)$。
