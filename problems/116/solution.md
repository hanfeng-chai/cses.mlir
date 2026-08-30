# 116 - Police Chase

## Problem / 题目

Find the minimum number of (two-way) streets to close so there is no route between the bank (crossing $1$) and the harbor (crossing $n$), and list those streets.

求需要关闭的最少（双向）街道数，使银行（路口 $1$）与港口（路口 $n$）之间没有路线，并列出这些街道。

## Idea / 思路

By the max-flow / min-cut theorem, the minimum number of streets to cut equals the **maximum flow** from $1$ to $n$ when each street has capacity $1$. We model every undirected street as two opposite capacity-$1$ arcs and run Dinic. After the flow saturates, the set $S$ of crossings reachable from the source in the residual graph defines the cut: every original street with exactly one endpoint in $S$ is a cut street, and their number equals the max flow. Any minimum cut is accepted, so a problem-specific checker (`checker.cpp`) confirms removing the listed streets disconnects $1$ from $n$ and the count is minimal.

由最大流/最小割定理，当每条街道容量为 $1$ 时，需切断的最少街道数等于从 $1$ 到 $n$ 的**最大流**。我们把每条无向街道建为两条相反的容量 $1$ 弧并运行 Dinic。流饱和后，残量图中从源可达的路口集合 $S$ 定义了割：每条恰有一个端点在 $S$ 中的原街道都是割边，其数量等于最大流。任意最小割都被接受，故题目专用 checker（`checker.cpp`）确认删除所列街道后 $1$ 与 $n$ 不连通且数量最小。

## Complexity / 复杂度

With unit capacities Dinic runs efficiently, well within the limits for $n \le 500$.

单位容量下 Dinic 运行高效，对 $n \le 500$ 远在时限内。
