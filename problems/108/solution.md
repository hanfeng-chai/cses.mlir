# 108 - Giant Pizza

## Problem / 题目

Each of $n$ family members gives two wishes "topping $x$ good/bad". Choose a set of toppings so that at least one wish of every member holds, or report `IMPOSSIBLE`.

$n$ 名家庭成员每人给出两个愿望"配料 $x$ 要/不要"。选一组配料使每人至少一个愿望成立，或报告 `IMPOSSIBLE`。

## Idea / 思路

This is a **2-SAT** problem: each member's two wishes form a clause (wish₁ OR wish₂). Build an implication graph on $2m$ literal nodes, adding $\lnot a \Rightarrow b$ and $\lnot b \Rightarrow a$ for each clause. Compute strongly connected components; the instance is satisfiable iff no variable shares an SCC with its negation. For the assignment, set each variable to the value whose literal lies in the SCC that comes later in topological order. Any valid assignment is accepted, so a problem-specific checker (`checker.cpp`) verifies every clause is satisfied.

这是 **2-SAT** 问题：每人的两个愿望构成一个子句（愿望₁ 或 愿望₂）。在 $2m$ 个文字节点上建蕴含图，对每个子句加 $\lnot a \Rightarrow b$ 和 $\lnot b \Rightarrow a$。求强连通分量；当没有变量与其否定同在一个 SCC 时可满足。赋值时把每个变量取其文字所在 SCC 在拓扑序中更靠后的那个值。任意合法赋值都被接受，故题目专用 checker（`checker.cpp`）校验每个子句被满足。

## Complexity / 复杂度

Building the graph and finding SCCs take $O(n+m)$.

建图与求 SCC 均为 $O(n+m)$。
