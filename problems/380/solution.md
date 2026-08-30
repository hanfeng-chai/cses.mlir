# 380 - School Excursion

## Problem / 题目

$n$ children each choose one of two attractions; $m$ pairs of children must choose the **same** one. Find every possible count of children that could end up at Korkeasaari.

$n$ 个孩子每人选择两个景点之一；$m$ 对孩子必须选择**相同**的景点。求所有可能出现在 Korkeasaari 的孩子人数。

## Idea / 思路

Build a **union-find** structure, merging $a$ and $b$ for every "must match" pair. Every connected component then must go *entirely* to one attraction or the other — there's no finer choice within a component. So if the component sizes are $s_1,\dots,s_c$, the set of achievable Korkeasaari head-counts is exactly the set of **subset sums** of $\{s_1,\dots,s_c\}$ (choose which components go to Korkeasaari).

Since $\sum s_i=n$, this is the classic "which sums from $0$ to $n$ are achievable" reachability problem, solved with a **bitset DP**: `reachable` starts as bit $0$ set; for each component size $s$, `reachable |= reachable << s` (a single word-shifted OR over the whole bitset). Finally read off bits $1$ through $n$ into the answer string.

*Sanity check:* $n=5$, pairs $(1,2),(2,3),(1,5)$ merge $\{1,2,3,5\}$ into one component of size $4$, leaving $\{4\}$ alone (size $1$). Reachable sums: $0,1,4,5$ — giving output bits $1,4,5$ set, i.e. `10011`, matching the sample.

构造一个**并查集**，对每一对"必须相同"的孩子 $a,b$ 做合并。之后每个连通分量必须*整体*去同一个景点——分量内部没有更细的选择。所以若各分量大小为 $s_1,\dots,s_c$，可能出现在 Korkeasaari 的人数集合，恰好就是 $\{s_1,\dots,s_c\}$ 的**子集和**集合（选哪些分量去 Korkeasaari）。

由于 $\sum s_i=n$，这正是经典的"$0$ 到 $n$ 中哪些和可达"的可达性问题，用**bitset DP**求解：`reachable` 初始只有第 $0$ 位为 $1$；对每个分量大小 $s$，做 `reachable |= reachable << s`（对整个 bitset 做一次按字移位再或运算）。最后读出第 $1$ 到 $n$ 位即为答案串。

*验证：* $n=5$，配对 $(1,2),(2,3),(1,5)$ 把 $\{1,2,3,5\}$ 合并成一个大小为 $4$ 的分量，剩下 $\{4\}$ 单独（大小 $1$）。可达和：$0,1,4,5$——对应输出第 $1,4,5$ 位为 $1$，即 `10011`，与样例一致。

## Complexity / 复杂度

$O(n+m)$ for union-find, $O(nc/w)$ for the bitset DP ($c$ = number of components, $w$ = machine word size), bounded by $O(n^2/w)$ in the worst case.

并查集 $O(n+m)$；bitset DP 为 $O(nc/w)$（$c$ 为分量数，$w$ 为机器字长），最坏情况 $O(n^2/w)$。
