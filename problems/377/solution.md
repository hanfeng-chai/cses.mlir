# 377 - Food Division

## Problem / 题目

$n$ children sit around a round table, each starting with $a_i$ units of food and wanting $b_i$. Each move transfers one unit of food between neighbors. Find the minimum number of moves to satisfy everyone.

$n$ 个孩子围坐一圈，每人有 $a_i$ 份食物、想要 $b_i$ 份。每次操作可以在邻居之间转移一份食物。求满足所有人需求的最少操作次数。

## Idea / 思路

Let $x_i$ be the net amount of food flowing from child $i$ to child $i+1$ (negative means flowing backward). Balancing child $i$ requires $x_{i-1}-x_i=a_i-b_i=:d_i$, i.e. $x_i=x_{i-1}-d_i$. Unrolling this recurrence, every $x_i$ is determined by a single free constant $c=x_0$ (the flow across one arbitrarily chosen edge, which is unconstrained since the table is circular) via $x_i=c-P_i$, where $P_i=d_1+\dots+d_i$ is a prefix sum.

The total number of moves is $\sum_i|x_i|=\sum_i|c-P_i|$ — a classic **L1 minimization**, minimized by choosing $c$ to be the **median** of $\{P_1,\dots,P_n\}$.

*Sanity check:* $a=[3,5,0],b=[2,4,2]$: $d=[1,1,-2]$, $P=[1,2,0]$, median $=1$. Cost $=|1-1|+|1-2|+|1-0|=0+1+1=2$ — matching the sample.

设 $x_i$ 为从孩子 $i$ 流向孩子 $i+1$ 的净食物量（负数表示反向流动）。孩子 $i$ 要平衡，需要 $x_{i-1}-x_i=a_i-b_i=:d_i$，即 $x_i=x_{i-1}-d_i$。展开这个递推式，每个 $x_i$ 都由一个自由常数 $c=x_0$（跨越任意选定一条边的流量，因为是圆桌所以不受约束）决定：$x_i=c-P_i$，其中 $P_i=d_1+\dots+d_i$ 是前缀和。

总操作次数是 $\sum_i|x_i|=\sum_i|c-P_i|$——经典的**L1 最小化**问题，取 $c$ 为 $\{P_1,\dots,P_n\}$ 的**中位数**时最小。

*验证：* $a=[3,5,0],b=[2,4,2]$：$d=[1,1,-2]$，$P=[1,2,0]$，中位数 $=1$。代价 $=|1-1|+|1-2|+|1-0|=0+1+1=2$——与样例一致。

## Complexity / 复杂度

$O(n\log n)$ time (sorting to find the median), $O(n)$ memory.

时间 $O(n\log n)$（排序求中位数），空间 $O(n)$。
