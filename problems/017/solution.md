# 017 - Chessboard and Queens

## Problem / 题目

Count the ways to place eight queens on an $8 \times 8$ board so that no two attack each other, where some squares are marked with `*` and may not hold a queen.

统计在 $8 \times 8$ 棋盘上放置八个皇后、使任意两个互不攻击的方案数，其中标记为 `*` 的格子不能放皇后。

## Idea / 思路

Backtrack row by row, placing exactly one queen per row. For the current row try every column $c$ that is not blocked and whose column and two diagonals are still free. We track occupancy with boolean arrays indexed by the column $c$, the anti-diagonal $r + c$, and the main diagonal $r - c + 7$ (the $+7$ keeps the index non-negative). Recurse to the next row, undo the marks on backtracking, and count one solution whenever all eight rows are filled.

逐行回溯，每行恰好放一个皇后。对当前行尝试每个未被封锁、且所在列与两条对角线都空闲的列 $c$。我们用布尔数组记录占用情况，分别以列 $c$、副对角线 $r + c$、主对角线 $r - c + 7$（加 $7$ 保证下标非负）为索引。递归到下一行，回溯时撤销标记，当八行全部放好时计一个方案。

## Complexity / 复杂度

The eight-queens search tree is tiny (well under $8!$ nodes thanks to the diagonal pruning), so the program finishes instantly.

八皇后的搜索树非常小（由于对角线剪枝，远小于 $8!$ 个节点），程序瞬间完成。
