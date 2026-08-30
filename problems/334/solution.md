# 334 - Grid Paths II

## Problem / 题目

Count monotone lattice paths from $(1,1)$ to $(n,n)$ that only move right or down, while avoiding $m$ given trap cells, modulo $10^9+7$. Here $n$ can be as large as $10^6$, but the number of traps $m$ is at most $1000$.

求从 $(1,1)$ 到 $(n,n)$、每步只能向右或向下、且要避开 $m$ 个陷阱格的单调路径数，对 $10^9+7$ 取模。$n$ 可以高达 $10^6$，但陷阱数 $m$ 至多 $1000$。

## Idea / 思路

With $n$ up to $10^6$ we obviously cannot DP over the whole grid; but since $m\le1000$, we can do a DP over just the *traps* (plus the destination), using the closed form for path counts: the number of unrestricted monotone paths between two points $(y_1,x_1)$ and $(y_2,x_2)$ (with $y_2\ge y_1$, $x_2\ge x_1$) is $\binom{(y_2-y_1)+(x_2-x_1)}{y_2-y_1}$.

Sort the traps by $(y,x)$. Define $f[i]$ = number of paths from the start to trap $i$ that avoid **every other trap** entirely (a "first-hit-free" path count). This is computed by inclusion–exclusion over earlier traps that could lie on such a path: start from the unrestricted path count to trap $i$, then subtract, for every earlier trap $j$ that lies weakly northwest of trap $i$ (i.e. $y_j\le y_i$ and $x_j\le x_i$, so a monotone path could pass through both), the quantity $f[j]\cdot(\text{paths from } j \text{ to } i)$ — this removes exactly those paths that hit trap $j$ first and then reach $i$ (they are illegal since they already touched a trap):

$$f[i]=\binom{\cdot}{\cdot}_{\text{start}\to i}-\sum_{j:\,\text{trap}_j\preceq \text{trap}_i} f[j]\cdot\binom{\cdot}{\cdot}_{j\to i}.$$

Finally the answer is the total unrestricted path count from start to $(n,n)$, minus the contribution of paths that hit any trap first:

$$\text{answer}=\binom{\cdot}{\cdot}_{\text{start}\to(n,n)}-\sum_i f[i]\cdot\binom{\cdot}{\cdot}_{i\to(n,n)}.$$

This is the standard "counting monotone lattice paths avoiding a small number of forbidden points" technique — instead of an $O(n^2)$ DP over the whole grid, we DP over the $O(m)$ obstacles, at $O(m^2)$ total cost, using precomputed factorials (up to $2n$, since the largest binomial argument is a path of length up to $2n-2$) for $O(1)$ path-count queries.

由于 $n$ 可达 $10^6$，显然不能对整张网格做 DP；但陷阱数 $m\le1000$，所以可以只对"陷阱点"（加上终点）做 DP，借助路径计数的封闭公式：两点 $(y_1,x_1)$ 到 $(y_2,x_2)$（$y_2\ge y_1,x_2\ge x_1$）之间不受限的单调路径数是 $\binom{(y_2-y_1)+(x_2-x_1)}{y_2-y_1}$。

把陷阱按 $(y,x)$ 排序。定义 $f[i]$ = 从起点到陷阱 $i$、且**完全避开其它所有陷阱**的路径数（"首次未撞陷阱"计数）。用容斥计算：从起点到 $i$ 的无限制路径数出发，对每个在陷阱 $i$ 左上方（弱偏序，即 $y_j\le y_i, x_j\le x_i$，意味着单调路径可能同时经过两者）的更早陷阱 $j$，减去 $f[j]\cdot(\text{从 } j \text{ 到 } i \text{ 的路径数})$——这样精确地去掉了"先撞上陷阱 $j$、再到达 $i$"的那些非法路径：

$$f[i]=\binom{\cdot}{\cdot}_{\text{起点}\to i}-\sum_{j:\,\text{trap}_j\preceq \text{trap}_i} f[j]\cdot\binom{\cdot}{\cdot}_{j\to i}。$$

最终答案是起点到 $(n,n)$ 的无限制路径数，减去"先撞上某个陷阱"的路径贡献：

$$\text{答案}=\binom{\cdot}{\cdot}_{\text{起点}\to(n,n)}-\sum_i f[i]\cdot\binom{\cdot}{\cdot}_{i\to(n,n)}。$$

这是"避开少量障碍点的单调路径计数"的标准技巧——不用对整张网格做 $O(n^2)$ 的 DP，而是只对 $O(m)$ 个障碍点做 DP，总代价 $O(m^2)$，配合预处理到 $2n$ 的阶乘（因为最大的组合数参数是长度至多 $2n-2$ 的路径）实现 $O(1)$ 路径数查询。

## Complexity / 复杂度

$O(n+m^2)$: $O(n)$ to precompute factorials up to $2n$, $O(m^2)$ for the trap DP (sorting is $O(m\log m)$, dominated by the $O(m^2)$ pairwise check). With $n\le10^6,\ m\le1000$ this is fast.

$O(n+m^2)$：预处理阶乘到 $2n$ 需 $O(n)$，陷阱 DP 需 $O(m^2)$（排序 $O(m\log m)$ 被两两枚举的 $O(m^2)$ 主导）。$n\le10^6,\ m\le1000$ 时运行很快。
