# 400 - Two Stacks Sorting

## Problem / 题目

A permutation arrives from left to right. Each value must be pushed onto one of two stacks, and stack tops may be popped to produce output $1,2,\dots,n$. Assign every input position to a stack, or report impossibility.

一个排列从左到右到达。每个值必须压入两个栈之一，并可从栈顶弹出以产生输出 $1,2,\dots,n$。为每个输入位置指定栈，或判断无解。

## Idea / 思路

### 1. Conflict graph / 冲突图

Consider positions $i<j$. They cannot use the same stack exactly in the following pattern:
$$a_i<a_j\quad\text{and}\quad \min_{k>j}a_k<a_i.$$
Why? When $a_j$ is pushed, it lies above $a_i$. The smaller future value $a_k<a_i$ means $a_i$ cannot yet be output before position $k$ arrives, but afterward $a_j>a_i$ blocks it from the top. Thus sorted output becomes impossible.

Create a graph whose vertices are input positions and whose edges are these conflicts. A valid stack assignment is exactly a 2-coloring of this graph:

- conflicting vertices must have different stack labels;
- conversely, if no same-color conflict exists, greedily pop the next required value whenever it appears on either top; the forbidden blocking pattern never occurs, so all values are output.

Hence the permutation is sortable iff the conflict graph is bipartite.

考虑位置 $i<j$。它们恰好在以下模式下不能放入同一栈：
$$a_i<a_j\quad\text{且}\quad\min_{k>j}a_k<a_i。$$
原因是：$a_j$ 入栈后位于 $a_i$ 上方；后面仍有更小值 $a_k<a_i$ 尚未到达，所以 $a_i$ 暂时不能输出；等 $a_k$ 到达后，较大的 $a_j$ 又挡在 $a_i$ 上面，无法按升序弹出。

建立冲突图，顶点为输入位置，边为上述冲突。合法栈分配恰好是该图的二染色：

- 冲突点必须使用不同栈；
- 反过来，若同色点间没有冲突，只要任一栈顶等于下一个期望值就立即弹出；上述唯一阻塞模式不会出现，因此能输出全部元素。

所以当且仅当冲突图是二分图时有解。

### 2. Active intervals / 活动区间

Precompute suffix minima. For each position $i$, binary-search the last position $R_i$ such that
$$\min_{k\ge R_i}a_k<a_i.$$
While processing a new position $j$, old vertex $i$ can conflict with $j$ only while $j\le R_i$. Schedule its expiration at $R_i+1$. Among active previous vertices, precisely those with $a_i<a_j$ conflict with $j$.

The conflict graph may have $O(n^2)$ edges, so they cannot be generated individually.

预处理后缀最小值。对每个位置 $i$，二分求最后一个位置 $R_i$，满足
$$\min_{k\ge R_i}a_k<a_i。$$
处理新位置 $j$ 时，旧点 $i$ 只有在 $j\le R_i$ 时仍可能与它冲突，因此把过期事件安排在 $R_i+1$。所有活动旧点中，恰好 $a_i<a_j$ 的点与 $j$ 冲突。

冲突边可能有 $O(n^2)$ 条，不能逐条生成。

### 3. DSU with opposite nodes / 带反色节点的并查集

Use $2n$ DSU nodes. Node $i$ means the color class containing vertex $i$; node $i+n$ means its opposite color class. A conflict edge $(i,j)$ imposes
$$i\equiv opposite(j),\qquad opposite(i)\equiv j,$$
implemented by two unions. If eventually `find(i)==find(i+n)`, the graph is not bipartite.

All vertices in one DSU root are already forced to have the same color. Therefore, when current $j$ conflicts with **any** active member of a root, adding one constraint against a representative imposes the correct relation for the entire root; the other potentially quadratic edges are redundant.

For every DSU root, maintain an ordered set of its active real vertices `(value, position)`. Expose only the minimum-valued active representative of each root in a segment tree. Repeatedly query the minimum representative among previous positions:

- if its value is at least $a_j$, no active component contains a conflicting value;
- otherwise record that representative's component, temporarily hide it, and continue;
- insert $j$, then add opposite-color DSU constraints for every recorded component.

Union active sets small-to-large. Each union reduces the number of DSU components, and every active element moves only logarithmically many times.

使用 $2n$ 个并查集节点。节点 $i$ 表示顶点 $i$ 所在颜色类，节点 $i+n$ 表示其反色类。冲突边 $(i,j)$ 要求
$$i\equiv opposite(j),\qquad opposite(i)\equiv j，$$
用两次合并实现。若最终 `find(i)==find(i+n)`，图不可二染色。

同一并查集根中的所有顶点已经被强制同色。因此，只要当前点 $j$ 与某个根中的**任意**活动成员冲突，向一个代表添加异色约束就会对整个根生效；其余可能二次数量的边都是冗余的。

为每个并查集根维护其活动真实顶点的有序集合 `(值,位置)`，在线段树中只暴露每个根的最小值代表。反复查询此前位置中的最小代表：

- 若其值不小于 $a_j$，任何活动分量都不含冲突值；
- 否则记录该代表所属分量，暂时隐藏它并继续；
- 插入 $j$ 后，对所有记录分量加入反色并查集约束。

活动集合采用小并大合并。每次 union 都减少分量数，每个活动元素只会移动对数次。

### 4. Extract and validate colors / 提取并验证颜色

Assign color 1 to an uncolored DSU root and color 2 to its opposite root, then label each original vertex by its root color. Finally simulate the two stacks and greedily pop the next expected value. This final simulation is a defensive verification and is also what the custom checker uses for arbitrary valid outputs.

对尚未染色的并查集根赋颜色1，对其反色根赋颜色2，再按根颜色给原顶点标号。最后模拟两个栈，并不断贪心弹出下一个期望值。这既是防御性验证，也是自定义 checker 验证任意参赛输出的方法。

## Complexity / 复杂度

Suffix searches and segment-tree operations take $O(n\log n)$. Small-to-large merging of ordered active sets costs $O(n\log^2 n)$ conservatively, with $O(n)$ DSU unions. Memory is $O(n)$. This fits $n\le2\cdot10^5$.

后缀二分和线段树操作为 $O(n\log n)$。活动有序集合的小并大合并保守为 $O(n\log^2 n)$，并查集合并次数为 $O(n)$。空间复杂度 $O(n)$，可通过 $n\le2\cdot10^5$。
