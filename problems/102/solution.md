# 102 - Planets Queries II

## Problem / 题目

Each of $n$ planets has one outgoing teleporter. For each query $(a,b)$, report the minimum number of teleportations to get from $a$ to $b$, or $-1$ if impossible.

$n$ 颗行星每颗有一个出向传送门。对每个询问 $(a,b)$，报告从 $a$ 到 $b$ 的最少传送次数，不可达则 $-1$。

## Idea / 思路

A functional graph is a set of "rho" shapes: trees whose edges point toward cycles. Decompose it: find every cycle (marking each cycle node with its cycle id, index, and the cycle length), then for each tree node compute its depth (steps to reach the cycle) and the cycle node it enters. With binary lifting for $k$-th successors, a query splits into cases. If $b$ is a tree node, $a$ reaches it only if $b$ is an ancestor of $a$ on its path to the cycle: jump $a$ up $depth[a]-depth[b]$ steps and check it equals $b$. If $b$ is on a cycle, $a$ must enter the **same** cycle; then the answer is $depth[a]$ plus the forward distance around the cycle from $a$'s entry to $b$.

函数图是一组"ρ"形：树边指向环。先分解：找出每个环（给每个环节点标上环号、环内下标、环长），再为每个树节点算出其深度（到达环的步数）和进入的环节点。配合 $k$ 次后继的二进制提升，查询分情况。若 $b$ 是树节点，则 $a$ 只有当 $b$ 是 $a$ 通往环路径上的祖先时才可达：把 $a$ 上跳 $depth[a]-depth[b]$ 步看是否等于 $b$。若 $b$ 在环上，则 $a$ 必须进入**同一**环；答案为 $depth[a]$ 加上从 $a$ 的入环点到 $b$ 沿环的正向距离。

## Complexity / 复杂度

Decomposition is $O(n)$, binary-lifting preprocessing $O(n\log n)$, each query $O(\log n)$.

分解 $O(n)$，二进制提升预处理 $O(n\log n)$，每个询问 $O(\log n)$。
