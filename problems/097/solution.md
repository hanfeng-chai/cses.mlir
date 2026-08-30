# 097 - Course Schedule

## Problem / 题目

Given $n$ courses and $m$ prerequisite constraints "$a$ before $b$", output an order to complete all courses, or `IMPOSSIBLE` if the constraints are contradictory.

给定 $n$ 门课程和 $m$ 条先修约束"$a$ 在 $b$ 之前"，输出一个完成所有课程的顺序，或在约束矛盾时输出 `IMPOSSIBLE`。

## Idea / 思路

This is a topological sort. Build the prerequisite graph and compute each course's in-degree. Repeatedly take a course with in-degree $0$ (no unmet prerequisites), append it to the order, and decrement its successors' in-degrees (Kahn's algorithm). If we manage to output all $n$ courses the order is valid; otherwise a cycle remained and the answer is `IMPOSSIBLE`. Any valid order is accepted, so a problem-specific checker (`checker.cpp`) verifies the output is a permutation respecting every constraint.

这是拓扑排序。建先修图并算每门课的入度。反复取一门入度为 $0$（无未满足先修）的课，接到顺序末尾，并把它后继的入度减一（Kahn 算法）。若能输出全部 $n$ 门课则顺序合法；否则残留了环，答案为 `IMPOSSIBLE`。任意合法顺序都被接受，故题目专用 checker（`checker.cpp`）校验输出是满足每条约束的排列。

## Complexity / 复杂度

Kahn's algorithm runs in $O(n+m)$.

Kahn 算法运行在 $O(n+m)$。
