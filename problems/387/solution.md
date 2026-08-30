# 387 - Grid Puzzle I

## Problem / 题目

Given target row sums $a_1,\dots,a_n$ and column sums $b_1,\dots,b_n$ for an $n\times n$ 0/1 grid, construct a grid meeting them exactly, or report it is impossible.

给定 $n\times n$ 0/1 网格每行的目标和 $a_1,\dots,a_n$ 与每列的目标和 $b_1,\dots,b_n$，构造一个满足要求的网格，或判断无解。

## Idea / 思路

This is the classical **Gale–Ryser** realizability problem for a bipartite degree sequence (rows vs. columns), and it has a simple greedy constructive proof: repeatedly take the row with the largest *remaining* required count $a_i$, and place its $1$s in exactly the $a_i$ columns that currently have the largest *remaining* required count $b_j$ (decrementing those $b_j$ by one each). If at any point a row needs more $1$s than there are columns with positive remaining capacity, no solution exists.

*Why greedy-by-largest-remaining works:* this is the standard proof technique for the Gale–Ryser theorem — giving the 1s of the largest row to the largest-capacity columns never "wastes" capacity that a later, smaller row might have uniquely needed (an exchange argument shows any valid solution can be rearranged into one consistent with this greedy choice). A priority queue (max-heap keyed by remaining $b_j$) makes each row's placement $O(a_i\log n)$.

After processing every row (in decreasing order of $a_i$), if the greedy never got stuck, all $b_j$ are automatically driven to $0$ exactly (guaranteed by $\sum a_i=\sum b_i$ combined with the greedy's correctness) — a defensive check re-verifies this before printing the grid.

Since **any** valid grid is accepted (multi-solution), the checker recomputes row/column sums from the participant's output and compares against $a,b$, and separately checks the IMPOSSIBLE/possible verdict against the jury.

这是二部图度序列（行 vs 列）的经典**Gale–Ryser**可行性问题，有一个简单的贪心构造性证明：反复选出**剩余**需求量 $a_i$ 最大的行，把它的 $1$ 放在当前**剩余**需求量 $b_j$ 最大的恰好 $a_i$ 个列上（每选中一个就把该列的 $b_j$ 减1）。如果某一步某行需要的 $1$ 的数量超过了剩余容量为正的列数，则无解。

*为什么"每次选最大剩余"的贪心是对的：* 这是 Gale–Ryser 定理的标准证明技巧——把最大行的 $1$ 分配给容量最大的列，永远不会"浪费"掉某个后续更小的行可能唯一需要的容量（交换论证可证明任何合法方案都能重排成与该贪心一致的形式）。用一个按剩余 $b_j$ 排序的大顶堆（优先队列），每行分配的复杂度是 $O(a_i\log n)$。

处理完所有行（按 $a_i$ 降序）后，如果贪心过程中从未卡住，所有 $b_j$ 会自动精确归零（由 $\sum a_i=\sum b_i$ 加上贪心的正确性保证）——代码中仍加了一次防御性检查，确认后再输出网格。

由于**任何**合法网格都算对（多解题），checker 会从参赛输出重新计算每行每列的和并与 $a,b$ 比较，并单独核对 IMPOSSIBLE/有解 的判定是否与裁判一致。

## Complexity / 复杂度

$n\le 50$. The greedy does $O(\sum a_i)\le O(n^2)$ heap pops/pushes, each $O(\log n)$, so overall $O(n^2\log n)$ — trivially fast.

$n\le50$。贪心过程做 $O(\sum a_i)\le O(n^2)$ 次堆的弹出/插入，每次 $O(\log n)$，总体 $O(n^2\log n)$，非常快。
