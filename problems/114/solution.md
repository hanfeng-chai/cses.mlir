# 114 - Knight's Tour

## Problem / 题目

Given a knight's starting square on an $8\times8$ board, output a sequence of moves visiting every square exactly once (printed as a grid of move numbers).

给定骑士在 $8\times8$ 棋盘上的起始格，输出一个访问每格恰好一次的走法序列（以走法编号网格输出）。

## Idea / 思路

We search for a Hamiltonian path of knight moves using **Warnsdorff's heuristic** inside a backtracking DFS: at each step, try the onward squares in increasing order of their own number of unvisited knight moves (move toward the most constrained square first). This heuristic almost always completes a tour with no backtracking on the $8\times8$ board, and the backtracking guarantees correctness if a greedy choice ever dead-ends. Any valid tour is accepted, so a problem-specific checker (`checker.cpp`) verifies all $64$ numbers form consecutive knight moves starting at the given square.

我们用**Warnsdorff 启发式**在回溯 DFS 中搜索骑士的哈密顿路径：每步按"目标格自身未访问骑士走法数"递增的顺序尝试（优先走向最受限的格子）。该启发式在 $8\times8$ 棋盘上几乎总能无回溯地完成巡游，而回溯保证了若贪心走入死路时仍能纠正。任意合法巡游都被接受，故题目专用 checker（`checker.cpp`）校验全部 $64$ 个编号构成自给定格起的连续骑士走法。

## Complexity / 复杂度

The board is fixed at $64$ squares; Warnsdorff ordering makes the search effectively linear in practice.

棋盘固定 $64$ 格；Warnsdorff 排序使搜索在实践中基本线性。
