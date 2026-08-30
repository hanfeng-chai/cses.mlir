# 312 - Tree Isomorphism II

## Problem / 题目
Decide whether two unrooted trees are isomorphic.

判断两棵无根树是否同构。

## Idea / 思路
A tree has one or two centers (found by repeatedly peeling leaves). Root each tree at each of its centers and compute the AHU canonical id (shared map). The trees are isomorphic iff some center-rooting of one matches some center-rooting of the other.

树有一个或两个中心（反复剥叶得到）。把每棵树分别以其各中心为根求 AHU 规范 id（共享映射）。两树同构当且仅当其中一棵某个中心根与另一棵某个中心根的 id 相同。

## Complexity / 复杂度
$O(n\log n)$ over the sum of sizes. 关于规模之和 $O(n\log n)$。
