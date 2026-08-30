# 305 - MST Edge Check

## Problem / 题目
For each edge of a weighted graph decide whether it can appear in *some* minimum spanning tree.

对加权图每条边，判断它能否出现在**某个**最小生成树中。

## Idea / 思路
Sort edges by weight and process them in weight groups with a union-find that already contains all strictly lighter edges. An edge can be in some MST iff its endpoints are in different components at that moment (it is a minimal crossing edge of a cut). After testing a whole weight group, union all of its edges.

按权排序并按权值分组处理；并查集此刻已包含所有严格更轻的边。一条边能进某棵 MST 当且仅当此刻其两端不在同一分量（它是某割的最小跨边）。测完整组后再合并组内所有边。

## Complexity / 复杂度
$O(m\log m)$. $O(m\log m)$。
