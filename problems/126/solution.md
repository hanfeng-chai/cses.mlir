# 126 - Hotel Queries

## Problem / 题目

There are $n$ hotels with free-room counts. For each of $m$ groups (in order) assign the **first** hotel having at least the required rooms, decreasing that hotel's free rooms; print the hotel or $0$.

有 $n$ 家旅馆，各有空房数。对 $m$ 个团队（按顺序）分配**第一家**空房数足够的旅馆并扣减其空房；输出旅馆编号或 $0$。

## Idea / 思路

Build a **segment tree of maximums** over the hotels (padded to a power of two for clean top-down descent). For a group needing $r$ rooms, if the global max is below $r$ print $0$; otherwise descend from the root, always going to the left child if its max is $\ge r$, else the right child. This lands on the leftmost hotel that can host the group; subtract $r$ there and update the path.

构建旅馆上的**最大值线段树**（补齐到 2 的幂以便自顶向下定位）。对需要 $r$ 间房的团队，若全局最大值小于 $r$ 输出 $0$；否则从根下降，左孩子最大值 $\ge r$ 就走左、否则走右，最终落到能接待该团的最左旅馆；在那里减去 $r$ 并更新路径。

## Complexity / 复杂度

Each group is handled in $O(\log n)$.

每个团队 $O(\log n)$ 处理。
