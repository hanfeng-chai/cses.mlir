# 140 - Range Updates and Sums

## Problem / 题目

Maintain an array under three operations: add $x$ to a range, assign $x$ to a range, and sum a range.

在三种操作下维护数组：区间加 $x$、区间赋值为 $x$、区间求和。

## Idea / 思路

Use a **segment tree with two lazy tags**: an assignment tag and an addition tag. When an assignment reaches a node it overrides any pending addition (and sets the sum to $x \times \text{length}$); a later addition stacks on top. When pushing tags down, apply the assignment first, then the addition, to children. Each node stores its range sum, kept consistent after every tagged update.

使用**带两个懒标记的线段树**：赋值标记与加法标记。当赋值到达某节点时覆盖其待处理的加法（并把和设为 $x \times \text{长度}$）；之后的加法叠加其上。下推标记时先对孩子施加赋值、再施加加法。每个节点存区间和，在每次带标记更新后保持一致。

## Complexity / 复杂度

Every operation is $O(\log n)$.

每个操作 $O(\log n)$。
