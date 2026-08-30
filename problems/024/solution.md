# 024 - Grid Paths

## Problem / 题目

In a $7 \times 7$ grid we walk from the upper-left square to the lower-left square, visiting **every** square exactly once (a Hamiltonian path of $48$ moves). A route is written as $48$ characters `U`/`D`/`L`/`R`. We are given a description in which some characters are replaced by `?` (a wildcard matching any direction); count how many complete routes match it.

在一个 $7 \times 7$ 的网格里，我们从左上角格子走到左下角格子，且**每个**格子恰好经过一次（一条 $48$ 步的哈密顿路径）。一条路线用 $48$ 个字符 `U`/`D`/`L`/`R` 表示。给定的描述中有些字符被替换成了 `?`（通配符，可匹配任意方向），要求统计有多少条完整路线与之相符。

## Idea / 思路

We do **backtracking**: at step $i$ we try the directions allowed by `description[i]` (a fixed letter forces one direction, `?` allows all four), mark the square as occupied, recurse, then unmark. The naive search branches up to $4^{48}$ times, which is astronomical, so two classic prunings (from the official hint) are essential. **(1) Early goal:** if we step onto the lower-left target before all $48$ moves are used, there is no valid completion (we would have to leave the end square and return, impossible for a path that ends there), so we stop. **(2) Split detection:** if the current square has walls on two opposite sides while the other two opposite sides are free, the still-empty region is cut into two halves that can never be merged into one path, so we stop. To make boundary checks trivial we embed the board in a $9 \times 9$ array with a surrounding ring of wall cells (sentinels).

我们采用**回溯搜索**：在第 $i$ 步尝试 `description[i]` 允许的方向（固定字母只能走一个方向，`?` 则四个方向都试），标记当前格已占用，递归，再撤销标记。朴素搜索最多会分支 $4^{48}$ 次，是天文数字，因此官方 hint 给出的两个经典剪枝至关重要。**(1) 提前到达终点：** 如果在用完全部 $48$ 步之前就踏上左下角终点，就不可能再合法完成（必须离开终点再绕回来，而以终点结束的路径无法做到），于是剪枝。**(2) 分割剪枝：** 如果当前格在某条轴上的两侧都是墙、而在另一条轴上的两侧都是空格，那么剩余的空白区域被切成了两块，再也无法连成一条路径，于是剪枝。为了让越界判断变简单，我们把棋盘嵌入一个 $9 \times 9$ 数组，四周围上一圈墙格子作为哨兵。

## Complexity / 复杂度

The search is exponential in the worst case, but on the hardest input (all $48$ characters are `?`) the two prunings shrink the recursion tree to only a few hundred thousand nodes, so the program finishes in well under half a second — comfortably inside the time limit.

最坏情况下搜索是指数级的，但在最难的输入（$48$ 个字符全是 `?`）上，这两个剪枝把递归树压缩到只有几十万个节点，因此程序在半秒以内就能跑完，远在时限之内。
