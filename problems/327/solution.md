# 327 - Border Subgrid Count I

## Problem / 题目

For each of the first $k$ letters, count square subgrids whose entire border consists of that letter. The grid size is up to $3000$, so all side lengths cannot be checked independently.

对前 $k$ 个字母分别统计：边框全部由该字母组成的正方形子网格数量。网格大小可达 $3000$，不能独立检查所有边长。

## Idea / 思路

A square is uniquely determined by its top-left cell $A=(y,x)$ and bottom-right cell $B=(y+s-1,x+s-1)$, which lie on the same main diagonal.

Precompute two reach values for every cell:

- `RD[A]`: the minimum of the same-letter run to the **right** and the run **downward** from $A$. It is the largest side length for which $A$ can supply the square's top and left borders.
- `LU[B]`: the minimum of the same-letter run to the **left** and the run **upward** from $B$. It is the largest side length for which $B$ can supply the bottom and right borders.

For two cells at diagonal indices $i<j$, they form a valid square of side $j-i+1$ exactly when:

1. their letters are equal;
2. `RD[i] >= j-i+1`;
3. `LU[j] >= j-i+1`.

Process each main diagonal from top-left to bottom-right. Maintain previous indices $i$ in one Fenwick tree per letter. An index $i$ is active while
$$j-i+1\le RD[i],$$
that is, until just before $j=i+RD[i]$. Schedule an expiration event at that index and remove it before answering the query there.

At bottom-right index $j$, condition 3 becomes
$$i\ge j-LU[j]+1.$$
Also $i\le j-1$ because side length $1$ is handled separately. Therefore query the active Fenwick entries of the same letter over
$$[j-LU[j]+1,\ j-1].$$
Every returned index gives exactly one valid square.

The grid has about nine million cells at maximum size. Traversing row-major arrays along diagonals causes large-stride cache misses, so the implementation stores `RD`, `LU`, and the letter values **contiguously by diagonal**. This reduced the largest local test from about $1.08$ seconds to about $0.68$ seconds. Fenwick counts fit in 16-bit signed integers because a diagonal has length at most $3000$.

一个正方形由左上角 $A=(y,x)$ 与右下角 $B=(y+s-1,x+s-1)$ 唯一确定，二者位于同一条主对角线上。

预处理每个格子的两个可达长度：

- `RD[A]`：从 $A$ 向**右**的同字母连续长度与向**下**连续长度的较小值，即 $A$ 能提供上边和左边的最大正方形边长；
- `LU[B]`：从 $B$ 向**左**的同字母连续长度与向**上**连续长度的较小值，即 $B$ 能提供下边和右边的最大正方形边长。

对同一对角线上下标 $i<j$ 的两个格子，它们恰好在以下条件同时成立时组成边长 $j-i+1$ 的合法正方形：

1. 两端字母相同；
2. `RD[i] >= j-i+1`；
3. `LU[j] >= j-i+1`。

沿每条主对角线从左上到右下扫描，并为每个字母维护一棵 Fenwick 树，存放此前仍有效的左上角下标 $i$。当
$$j-i+1\le RD[i]$$
时 $i$ 有效，即在 $j=i+RD[i]$ 之前有效。把删除事件安排在这个下标，并在查询该位置前删除。

对当前右下角 $j$，条件3等价于
$$i\ge j-LU[j]+1。$$
又因为边长1的正方形单独统计，所以 $i\le j-1$。因此只需查询同字母 Fenwick 树上的区间
$$[j-LU[j]+1,\ j-1]。$$
返回的每个下标都对应唯一一个合法正方形。

最大规模约有九百万个格子。若按行存储数组、再沿对角线访问，会产生大步长缓存缺失；实现把 `RD`、`LU` 与字母值按**对角线连续存储**。这使最大本地测试从约 $1.08$ 秒降到约 $0.68$ 秒。Fenwick 计数可用16位有符号整数，因为对角线长度不超过3000。

## Complexity / 复杂度

Each cell performs $O(\log n)$ Fenwick work once, so time is $O(n^2\log n)$. Precomputed reaches and colors use $O(n^2)$ memory; Fenwick trees use $O(kn)$.

每个格子只做一次 $O(\log n)$ 的 Fenwick 操作，时间复杂度为 $O(n^2\log n)$。预处理的长度和字母占 $O(n^2)$ 空间，Fenwick 树占 $O(kn)$。
