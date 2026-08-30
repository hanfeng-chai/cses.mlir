# 314 - Critical Cities

## Problem / 题目
Find all cities that lie on **every** route from city $1$ to city $n$.

求位于从城市 $1$ 到城市 $n$ 的**每条**路线上的所有城市。

## Idea / 思路
A city is critical iff it dominates $n$ in the flow graph rooted at $1$. Compute the dominator tree with the iterative Cooper–Harvey–Kennedy algorithm (reverse-postorder fixpoint with finger-style `intersect`). The critical cities are exactly the chain of immediate dominators from $n$ up to $1$.

一座城市关键当且仅当它在以 $1$ 为根的图中支配 $n$。用迭代的 Cooper–Harvey–Kennedy 算法（逆后序不动点 + finger 式 `intersect`）求支配树。关键城市恰为从 $n$ 沿直接支配者上溯到 $1$ 的链。

## Complexity / 复杂度
Near-linear $O((n+m)\alpha)$ in practice. 实际近线性 $O((n+m)\alpha)$。
