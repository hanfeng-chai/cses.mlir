# 323 - Filled Subgrid Count I

## Problem / 题目

Given an $n\times n$ grid of letters (from an alphabet of $k$ letters), count, for each letter, how many **square** subgrids are monochromatic (every cell inside equals that letter).

给定一个 $n\times n$ 的字母网格（字母表大小为 $k$），对每个字母，统计有多少个**正方形**子网格是单色的（内部所有格子都是该字母）。

## Idea / 思路

This is the classic "maximal square" DP, repurposed for *counting* instead of just finding the largest square. Let $dp[i][j]$ be the size of the largest monochromatic square whose bottom-right corner is exactly cell $(i,j)$ (so the square only uses the letter $g[i][j]$). The transition is:

- If $(i,j)$ is on the top row or left column, $dp[i][j]=1$ (a single cell is always a valid $1\times1$ square).
- Otherwise, if $g[i][j]=g[i-1][j]=g[i][j-1]=g[i-1][j-1]$, then $dp[i][j]=\min(dp[i-1][j],\,dp[i][j-1],\,dp[i-1][j-1])+1$ — the largest same-letter square anchored here is limited by the smallest of the three neighboring squares (the classic "min of three neighbors" argument: a $(s+1)\times(s+1)$ square anchored at $(i,j)$ exists iff all three neighboring anchors support a square of size $\ge s$ *and* the new border cells share the letter).
- Otherwise $dp[i][j]=1$ (the four cells are not all identical, so no bigger square can be anchored here).

The key extra observation that turns this into a **counting** DP is: every square nested inside the maximal square anchored at $(i,j)$ (i.e. every size from $1$ up to $dp[i][j]$, all sharing the same bottom-right corner) is *also* monochromatic, because it is literally a sub-region of a region that is already known to be one uniform letter. So $dp[i][j]$ is not just "the biggest square here" — it is exactly **the number of monochromatic squares whose bottom-right corner is $(i,j)$**. Summing $dp[i][j]$ over the whole grid, split by the letter $g[i][j]$, gives the final per-letter answer, because every monochromatic square has one unique bottom-right corner, so this sums each square exactly once.

The implementation keeps only two rows (`prev`/`cur`) instead of a full $n\times n$ table to save memory, since $dp[i][\cdot]$ only depends on row $i-1$.

这是经典的"最大正方形" DP，这里改用来做**计数**而不是只求最大边长。设 $dp[i][j]$ 为以 $(i,j)$ 为右下角、且内部全部同色（等于 $g[i][j]$）的最大正方形边长。转移：

- 若 $(i,j)$ 在第一行或第一列，$dp[i][j]=1$（单个格子总是合法的 $1\times1$ 正方形）。
- 否则若 $g[i][j]=g[i-1][j]=g[i][j-1]=g[i-1][j-1]$，则 $dp[i][j]=\min(dp[i-1][j],\,dp[i][j-1],\,dp[i-1][j-1])+1$——三个邻居中最小的那个决定了能扩展出的正方形边长上限（经典的"三邻居取 min"论证：以 $(i,j)$ 为右下角能有边长 $s+1$ 的同色正方形，当且仅当三个相邻锚点都支持边长 $\ge s$ 的正方形，且新增的边上格子颜色也一致）。
- 否则 $dp[i][j]=1$（四个格子颜色不全相同，无法在此扩展出更大的正方形）。

把这个 DP 变成"计数"的关键在于：以 $(i,j)$ 为右下角的最大正方形内部，所有从边长 $1$ 到 $dp[i][j]$ 的**同角**正方形也都是单色的——因为它们本就是一块已知单色区域的子区域。所以 $dp[i][j]$ 不只是"这里最大能有多大"，而恰好就是**以 $(i,j)$ 为右下角的单色正方形个数**。把 $dp[i][j]$ 按格子颜色 $g[i][j]$ 分组累加到答案里，因为每个单色正方形有唯一的右下角，这样恰好不重不漏地数了一遍。

实现上只保留两行（`prev`/`cur`）而非整张 $n\times n$ 表来省内存，因为第 $i$ 行的 $dp$ 只依赖第 $i-1$ 行。

## Complexity / 复杂度

$O(n^2)$ time, $O(n)$ extra memory (two rolling rows) plus the $O(n^2)$ grid itself. With $n\le3000$ this is about $9\times10^6$ simple operations.

时间 $O(n^2)$，额外空间 $O(n)$（两行滚动数组）加上网格本身的 $O(n^2)$。$n\le3000$ 时约 $9\times10^6$ 次简单操作，轻松通过。
