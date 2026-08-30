# 385 - Coin Arrangement

## Problem / 题目

A $2\times n$ grid holds $2n$ coins in total. Using unit moves (move one coin one step up/down/left/right), rearrange the coins so every cell holds exactly one coin. Find the minimum number of moves.

$2\times n$ 网格中一共有 $2n$ 个硬币。每次操作把一个硬币朝上下左右移动一步，求让每个格子恰好有一个硬币所需的最少操作数。

## Idea / 思路

Let column $i$ have $a_i$ coins in row 1 and $b_i$ coins in row 2. Introduce, for each column, an unknown net **vertical transfer** $v_i$ (coins moved from row 1 to row 2 within that column; $v_i$ may be negative). After the vertical transfers, row 1's "adjusted supply" at column $i$ is $a_i-v_i$ and row 2's is $b_i+v_i$; each row must now be individually balanced via **horizontal** moves to reach exactly $1$ per cell — the classic 1‑D "equalize an array via adjacent transfers" problem, whose minimum cost is $\sum_i |P_i|$ where $P_i$ is the running prefix sum of (supply $-$ target).

So with $P^1_i=\sum_{j\le i}(a_j-1-v_j)$ and $P^2_i=\sum_{j\le i}(b_j-1+v_j)$ (both must end at $P^1_n=P^2_n=0$, since flow cannot leave the grid), the total cost is
$$\sum_i |v_i| \;+\; \sum_{i=1}^{n-1}\big(|P^1_i|+|P^2_i|\big).$$
Since $P^1_i+P^2_i=\sum_{j\le i}(a_j+b_j-2)=:C_i$ is *fixed* (independent of the $v_j$'s), the only real freedom is choosing $P^1_i$ (then $P^2_i=C_i-P^1_i$ is determined).

This is exactly a **slope-trick DP** over the state $p=P^1_i$: define $g_i(p)$ = minimum cost using $i$ vertical transfers and $i-1$ boundary terms, ending with $P^1_i=p$. The transition $g_i(p)=\min_{p'} g_{i-1}(p')+|p'+a_i-1-p|$ is a shift of the domain by $a_i-1$ followed by a min-plus convolution with $|\cdot|$ — and convolving a convex function with $|\cdot|$ has the well-known effect of **clipping its slopes to magnitude $\le 1$** (verified directly: $\min_x 2|x|+|x-z|=|z|$, i.e. a slope-2 kink gets clipped to slope 1). In the standard two-heap slope-trick representation (max-heap $L$ for left breakpoints, min-heap $R$ for right breakpoints), this clip is simply: keep only the single largest element of $L$ and the single smallest element of $R$. Then add the two V-shapes $|p|$ and $|p-C_i|$ (the boundary term) via the classic "add $|x-c|$" heap operation. Because of the clip, the heaps never grow beyond ~3 elements, so every step is $O(1)$.

*A pitfall that cost real debugging time:* the boundary term must use the **cumulative** $C_i=\sum_{j\le i}(a_j+b_j-2)$, not the per-column value $a_i+b_i-2$ — using the per-column value silently gives wrong (too-small) answers, caught only by tracing a failing case back through the recursion by hand and comparing against a brute-force $O(n!)$ assignment search on tiny random grids.

设第 $i$ 列第一行有 $a_i$ 个硬币、第二行有 $b_i$ 个。为每列引入一个未知的**竖直净转移量** $v_i$（该列内从第一行移到第二行的硬币数，可为负）。转移之后，第一行在列 $i$ 的"调整后供给"为 $a_i-v_i$，第二行为 $b_i+v_i$；随后每一行都需要通过**水平**移动独立地把每格调整为恰好1个——这正是经典的一维"通过相邻转移使数组相等"问题，其最小代价为 $\sum_i|P_i|$，其中 $P_i$ 是（供给 $-$ 目标）的前缀和。

令 $P^1_i=\sum_{j\le i}(a_j-1-v_j)$、$P^2_i=\sum_{j\le i}(b_j-1+v_j)$（二者末项都必须为0，因为流量无法流出网格），总代价为
$$\sum_i|v_i|+\sum_{i=1}^{n-1}\big(|P^1_i|+|P^2_i|\big)。$$
由于 $P^1_i+P^2_i=\sum_{j\le i}(a_j+b_j-2)=:C_i$ 是（与所有 $v_j$ 无关的）**固定量**，真正自由的只是选择 $P^1_i$（$P^2_i=C_i-P^1_i$ 随之确定）。

这正是一个关于状态 $p=P^1_i$ 的**Slope Trick DP**：设 $g_i(p)$ 为使用 $i$ 次竖直转移、$i-1$ 个边界项、末尾 $P^1_i=p$ 的最小代价。转移 $g_i(p)=\min_{p'}g_{i-1}(p')+|p'+a_i-1-p|$ 是先把定义域平移 $a_i-1$，再与 $|\cdot|$ 做 min-plus 卷积——而凸函数与 $|\cdot|$ 卷积的效果是众所周知的**把斜率截断到不超过1**（直接验证：$\min_x 2|x|+|x-z|=|z|$，斜率2的折点被截成斜率1）。在标准的双堆 slope trick 表示中（大顶堆 $L$ 存左侧折点，小顶堆 $R$ 存右侧折点），这个截断操作就是：只保留 $L$ 中最大的一个、$R$ 中最小的一个。然后再用经典的"加 $|x-c|$"堆操作依次叠加两个V形函数 $|p|$、$|p-C_i|$（边界项）。由于每步都会截断，堆的大小永远不超过约3个元素，每步 $O(1)$。

**曾造成真实调试成本的陷阱：** 边界项必须使用**累积**的 $C_i=\sum_{j\le i}(a_j+b_j-2)$，而不是单列的 $a_i+b_i-2$——用单列值会悄悄给出偏小的错误答案，只有通过手工回溯某个失败样例的递推过程、并与小规模随机网格上的 $O(n!)$ 暴力分配搜索对比才发现。

## Complexity / 复杂度

Each of the $n$ columns does $O(1)$ heap work (heaps capped at size 3), so the whole algorithm is $O(n)$ (or $O(n\log 1)=O(n)$), comfortably within limits for $n\le 10^5$.

每列的堆操作是 $O(1)$（堆大小不超过3），整体算法 $O(n)$，$n\le10^5$ 内轻松通过。
