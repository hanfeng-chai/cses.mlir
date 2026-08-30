# 355 - Subarray Sum Constraints

## Problem / 题目

Construct an array $x_1,\dots,x_n$ satisfying $m$ constraints of the form "$x_l+\dots+x_r=s$", or report that none exists.

构造数组 $x_1,\dots,x_n$，使其满足 $m$ 条"$x_l+\dots+x_r=s$"形式的约束，或判断无解。

## Idea / 思路

Work with prefix sums $P_0=0,\ P_i=x_1+\dots+x_i$. A constraint $(l,r,s)$ says exactly $P_r-P_{l-1}=s$, i.e. a **difference constraint** between two prefix-sum nodes. Build a graph on nodes $0,\dots,n$ with an edge $(l-1)\leftrightarrow r$ carrying the required difference $s$ (and $-s$ in the other direction).

This is the classic "difference-constraint system solved by BFS/DFS on each connected component": pick a root value for each component (node $0$ **must** be rooted at $P_0=0$, since it's the sum of zero elements; any other component, having no forced anchor, may pick any root, e.g. $0$), then propagate: whenever we traverse edge $(u,v,\delta)$ from an already-assigned $u$, assign $P_v=P_u+\delta$; if $v$ is *already* assigned and disagrees, the constraints are contradictory — print `NO`. If every component is internally consistent, recover $x_i=P_i-P_{i-1}$.

Since several arrays can satisfy the same constraints, this problem is graded with a custom checker that re-derives the prefix sums from the printed array and re-checks every $(l,r,s)$ triple, rather than comparing to one fixed expected array.

用前缀和 $P_0=0,\ P_i=x_1+\dots+x_i$ 来处理。约束 $(l,r,s)$ 恰好就是 $P_r-P_{l-1}=s$，即两个前缀和节点之间的一个**差分约束**。在节点 $0,\dots,n$ 上建图，为每条约束加一条边 $(l-1)\leftrightarrow r$，权值为所需差值 $s$（反方向为 $-s$）。

这是经典的"差分约束系统，靠对每个连通分量做 BFS/DFS 求解"：给每个连通分量选一个根的取值（节点 $0$ **必须**取 $P_0=0$，因为它是零个元素的和；其它没有强制锚点的分量可以任选根值，比如 $0$），然后传播：沿边 $(u,v,\delta)$ 从已确定的 $u$ 出发，令 $P_v=P_u+\delta$；如果 $v$ 已经被赋值且与之矛盾，说明约束互相冲突——输出 `NO`。如果所有分量内部都自洽，就用 $x_i=P_i-P_{i-1}$ 还原数组。

由于满足同一组约束的数组可能不止一个，本题用自定义 checker 评测：从输出的数组重新算出前缀和，逐一重新检查每条 $(l,r,s)$ 约束，而不是与某个固定的期望数组比较。

## Complexity / 复杂度

$O(n+m)$ time and memory for building the graph and doing BFS/DFS over all components.

建图与对所有连通分量做 BFS/DFS，时间和空间均为 $O(n+m)$。
