# 349 - Nearest Campsites I

## Problem / 题目

Given $n$ reserved and $m$ free campsites on an integer grid, find the **maximum**, over all free campsites, of the Manhattan distance to the nearest reserved campsite.

给定整数网格上 $n$ 个已预订和 $m$ 个空闲的营地，求所有空闲营地中，到最近已预订营地的曼哈顿距离的**最大值**。

## Idea / 思路

This is a classic nearest-neighbor search problem: build a **$k$-d tree** over the $n$ reserved points (alternately splitting on $x$ and $y$ at the median, so the tree has depth $O(\log n)$), then run a nearest-neighbor query for each of the $m$ free points and take the overall maximum of the $m$ answers.

The nearest-neighbor search recursively visits the child on the query's side of the split first, then decides whether the *other* child could possibly contain something closer. The naive pruning rule (compare the current best distance only to the gap along the single split axis) is correct but can be weak and lead to excessive exploration on adversarial/structured inputs. Instead, each subtree stores the **bounding box** (min/max $x$ and $y$) of all points inside it; the Manhattan distance from the query point to this box (zero if the query is already inside the box's projection, otherwise the sum of the two axis-wise gaps) is a valid lower bound on the distance to *any* point in that subtree, so an entire subtree can be skipped the moment this bound is $\ge$ the current best — a much tighter and more robust prune than only looking at the split value.

这是经典的最近邻搜索问题：对 $n$ 个已预订点建一棵 **k-d 树**（交替按 $x,y$ 的中位数分割，树深 $O(\log n)$），然后对 $m$ 个空闲点各做一次最近邻查询，取这 $m$ 个结果的最大值。

最近邻搜索递归地先访问查询点所在一侧的子树，再判断*另一侧*子树是否可能藏着更近的点。朴素的剪枝规则（只把当前最优距离与"沿分割轴的间隔"比较）是正确的，但在对抗性/结构化的输入上可能偏弱、导致过多无谓的搜索。改进做法是让每棵子树都保存其内部所有点的**包围盒**（$x,y$ 的最小/最大值）；查询点到这个包围盒的曼哈顿距离（若查询点的投影已经落在包围盒内则为零，否则为两个坐标轴方向间隔之和）是该子树内*任意*点到查询点距离的合法下界，一旦这个下界 $\ge$ 当前最优解，就可以直接跳过整棵子树——这比只看分割值本身要紧得多、也稳健得多。

## Complexity / 复杂度

Building the $k$-d tree is $O(n\log n)$ (median-finding via `nth_element` at each of $O(\log n)$ levels). Each of the $m$ queries is $O(\log n)$ on average with the bounding-box prune. Overall about $O((n+m)\log n)$.

建树 $O(n\log n)$（每层用 `nth_element` 找中位数，共 $O(\log n)$ 层）。有了包围盒剪枝后，$m$ 次查询平均每次 $O(\log n)$。总体约 $O((n+m)\log n)$。
