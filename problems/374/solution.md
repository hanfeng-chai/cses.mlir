# 374 - K Subset Sums I

## Problem / 题目

Find the $k$ smallest subset sums of an array of $n$ integers (which may be negative), including the empty subset (sum $0$).

求 $n$ 个整数（可能为负）的数组中，最小的 $k$ 个子集和（包括空子集，和为 $0$）。

## Idea / 思路

**Remove negatives first.** The globally smallest possible subset sum is obtained by taking *every* negative element (call this `base`, the sum of all negative $x_i$) and no positive ones. Toggling any single element $i$ in or out of a subset changes the sum by exactly $\pm x_i$ relative to some baseline — and crucially, whether $x_i$ is originally positive or negative, "toggling it away from its natural base state" always *costs* $|x_i|\ge0$. So every reachable subset sum equals `base + (some subset sum of the non-negative array $Y=\{|x_1|,\dots,|x_n|\}$)`, and this correspondence is an exact bijection between subsets of $X$ and subsets of $Y$. The problem reduces to: find the $k$ smallest subset sums of a **non-negative** array.

**$k$ smallest subset sums of a non-negative array, via a heap.** Sort $Y$ ascending. The smallest sum is $0$ (empty set) — that's rank $1$ immediately. For the rest, maintain a min-heap of states $(\text{sum}, i)$, meaning "this subset's largest included index is $i$". Seed it with $(Y_0, 0)$ (the subset $\{Y_0\}$). Popping the smallest state gives the next-smallest sum; from state $(\text{sum},i)$, two new subsets extend it minimally: **include the next element too** $(\text{sum}+Y_{i+1},\,i+1)$, or **swap the current last element for the next one** $(\text{sum}-Y_i+Y_{i+1},\,i+1)$. Every non-empty subset of $Y$ is reached this way exactly once (as the set of "largest-so-far chosen index" transitions forms a tree covering all subsets), so popping $k-1$ times after the initial $0$ gives the $k$ smallest sums in order.

*Sanity check:* $x=[1,6,3,-3]$, $k=9$: `base=-3`, $Y=[1,3,3,6]$ sorted. Running the heap gives deltas $0,1,3,3,4,4,6,6,7$, so the answers are `base+delta` $=-3,-2,0,0,1,1,3,3,4$ — exactly the sample output.

**先去掉负数。** 全局最小的子集和，是取*所有*负数元素（记为 `base`，即所有负的 $x_i$ 之和）、不取任何正数得到的。把某个元素 $i$ 从其"自然基准状态"切换进/出子集，都会让和恰好变化 $\pm x_i$——关键在于，无论 $x_i$ 原本是正是负，"把它从自然基准状态切换开"的代价永远是 $|x_i|\ge0$。所以每一个可达的子集和都等于 `base + (非负数组 $Y=\{|x_1|,\dots,|x_n|\}$ 的某个子集和)`，而且这是 $X$ 的子集与 $Y$ 的子集之间的一一对应。问题就化为：求一个**非负**数组的最小 $k$ 个子集和。

**非负数组的最小 $k$ 个子集和，用堆求。** 把 $Y$ 从小到大排序。最小的和是 $0$（空集）——直接是第 $1$ 名。剩下的用一个最小堆维护状态 $(\text{sum}, i)$，表示"这个子集里最大的下标是 $i$"。初始放入 $(Y_0, 0)$（子集 $\{Y_0\}$）。每次弹出最小状态，就得到下一个最小和；从状态 $(\text{sum},i)$ 出发，有两种"最小代价"的扩展方式：**再多包含下一个元素** $(\text{sum}+Y_{i+1},\,i+1)$，或**把当前最后一个元素换成下一个** $(\text{sum}-Y_i+Y_{i+1},\,i+1)$。这样一来，$Y$ 的每个非空子集都恰好被访问一次（"目前选中的最大下标"的转移关系构成一棵覆盖所有子集的树），所以在初始的 $0$ 之后再弹出 $k-1$ 次，就依次得到最小的 $k$ 个和。

*验证：* $x=[1,6,3,-3]$，$k=9$：`base=-3`，排序后 $Y=[1,3,3,6]$。跑一遍堆得到增量 $0,1,3,3,4,4,6,6,7$，所以答案是 `base+增量` $=-3,-2,0,0,1,1,3,3,4$——与样例输出完全一致。

## Complexity / 复杂度

$O(n\log n)$ to sort, $O(k\log k)$ for the heap (each of the $k$ pops pushes at most $2$ new states). Overall $O(n\log n+k\log k)$.

排序 $O(n\log n)$，堆操作 $O(k\log k)$（每弹出一个状态最多再压入 $2$ 个）。总体 $O(n\log n+k\log k)$。
