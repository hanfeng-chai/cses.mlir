# 344 - Swap Game

## Problem / 题目

Given a $3\times3$ grid containing $1,\dots,9$, find the minimum number of adjacent swaps (any two horizontally/vertically adjacent cells) needed to reach the sorted arrangement $1,2,3/4,5,6/7,8,9$.

给定一个包含 $1,\dots,9$ 的 $3\times3$ 网格，每次可以交换任意两个（水平或竖直）相邻格子，求变成 $1,2,3/4,5,6/7,8,9$ 所需的最少交换次数。

## Idea / 思路

There are only $9!=362880$ possible arrangements, and the "12 adjacent cell pairs of a $3\times3$ grid" define a fixed, small set of allowed swap-moves — exactly the setting for a plain **BFS** over the state graph (state = arrangement, edge = one allowed swap), which always finds the shortest path (= minimum number of swaps) in an unweighted graph.

Each state is turned into a unique integer in $[0,362880)$ via its **Lehmer code** (factorial number system): for each position, count how many of the *remaining* elements (to its right) are smaller than it, and combine those counts with factorial place values — a standard, collision-free way to rank a permutation. This lets us use a plain array (instead of a hash map) for the BFS visited/distance table, indexed by rank.

BFS starts from the given arrangement, generates neighbors by trying each of the 12 allowed adjacent swaps, and stops as soon as the sorted target arrangement is generated (whose distance is then the answer).

只有 $9!=362880$ 种排列，而"$3\times3$ 网格里 12 对相邻格子"给出了一个固定且很小的合法交换（走一步）集合——这正是普通 **BFS** 的典型场景（状态=排列，边=一次合法交换），在无权图上 BFS 总能找到最短路（=最少交换次数）。

把每个状态映射成 $[0,362880)$ 内唯一的整数，用的是**Lehmer 编码**（阶乘进制）：对每个位置，数一数它右边还剩下的元素中有多少个比它小，再结合阶乘位权组合起来——这是给排列编号且不会冲突的标准方法。这样就能用普通数组（而不是哈希表）做 BFS 的已访问/距离表，按编号直接索引。

BFS 从给定排列出发，尝试 12 种合法相邻交换生成邻居，一旦生成了排好序的目标排列就立即停止（此时的距离就是答案）。

## Complexity / 复杂度

At most $9!=362880$ states, each with $12$ neighbors and $O(81)$ work to rank a state, so the whole BFS is bounded by roughly $362880\times12\times81\approx3.5\times10^8$ in the worst case — but it terminates as soon as the (typically much closer) target is reached, and memory is a single array of size $9!$.

最多 $9!=362880$ 个状态，每个状态 $12$ 条邻边，每次排列编号 $O(81)$，最坏情况整个 BFS 上界约 $362880\times12\times81\approx3.5\times10^8$——但一旦（通常近得多的）目标被生成就立刻停止；内存只是一个大小为 $9!$ 的数组。
