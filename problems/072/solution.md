# 072 - Minimal Grid Path

## Problem / 题目

In an $n \times n$ grid of letters, move from the upper-left to the lower-right square going only right or down. Output the lexicographically minimal string formed along the way.

在一个 $n \times n$ 的字母网格中，从左上角走到右下角，只能向右或向下。输出沿途构成的字典序最小的字符串。

## Idea / 思路

Process the grid along anti-diagonals (cells with the same $i+j$). Keep the set of cells reachable by some lexicographically-optimal prefix. To extend to the next diagonal, expand every active cell to its right and down neighbours, look at their letters, take the **minimum** letter, append it to the answer, and keep only the candidate cells carrying that minimum letter. Greedily choosing the smallest letter at each step yields the lexicographically minimal full path.

沿反对角线（$i+j$ 相同的格子）处理网格。维护一个"被某个字典序最优前缀到达"的活动格子集合。要扩展到下一条对角线，把每个活动格子向右、向下扩展，查看它们的字母，取**最小**字母接到答案上，并只保留携带该最小字母的候选格子。每步贪心选最小字母即得字典序最小的完整路径。

## Complexity / 复杂度

Each cell is touched a constant number of times across the diagonals, so the time is $O(n^2)$.

每个格子在所有对角线中被访问常数次，因此时间为 $O(n^2)$。
