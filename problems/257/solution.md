# 257 - Task Assignment

## Problem / 题目
Assign each of $n$ employees to a distinct task minimizing the total cost; also output an optimal assignment.

把 $n$ 名员工各分配一项不同任务，最小化总费用；并输出一种最优分配。

## Idea / 思路
This is the assignment problem, solved by the Hungarian algorithm in $O(n^3)$. It maintains dual potentials for rows and columns and augments along equality-graph paths until a perfect matching of minimum cost is found.

这是指派问题，用匈牙利算法 $O(n^3)$ 求解。它维护行与列的对偶势，沿等式子图的路径增广，直至得到最小费用的完美匹配。

## Multi-solution / 多解
Any optimal assignment is accepted, so a custom checker verifies the assignment is a permutation whose cost equals the optimum reported by the jury.

任意最优分配均可接受，故自定义 checker 验证分配是一个排列，且其费用等于标程给出的最优值。

## Complexity / 复杂度
$O(n^3)$. $O(n^3)$。
