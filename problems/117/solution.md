# 117 - School Dance

## Problem / 题目

Given boys, girls, and a list of acceptable boy–girl pairs, find a maximum set of pairs using each person at most once, and list them.

给定男孩、女孩以及可接受的男女配对列表，求每人至多用一次的最大配对集合并列出。

## Idea / 思路

This is **maximum bipartite matching**. We use Kuhn's augmenting-path algorithm: for each boy, run a DFS that tries to match him to an acceptable girl, recursively re-matching the girl's current partner to free her up. Every successful augmenting path increases the matching by one. The matched pairs at the end form a maximum matching. Any maximum matching is accepted, so a problem-specific checker (`checker.cpp`) verifies the pairs are valid, disjoint, and as many as the optimum.

这是**二分图最大匹配**。我们用 Kuhn 增广路算法：对每个男孩，跑一个 DFS 尝试把他匹配到一个可接受的女孩，必要时递归地为该女孩当前的舞伴重新找人以腾出她。每条成功的增广路使匹配数加一。最终的匹配对构成最大匹配。任意最大匹配都被接受，故题目专用 checker（`checker.cpp`）校验配对合法、不相交、且数量达到最优。

## Complexity / 复杂度

Kuhn's algorithm runs in $O(V \cdot E)$, comfortable for the given limits.

Kuhn 算法运行在 $O(V \cdot E)$，对给定规模很从容。
