# 311 - Tree Isomorphism I

## Problem / 题目
Decide whether two rooted trees are isomorphic.

判断两棵有根树是否同构。

## Idea / 思路
Use AHU canonical labelling: process nodes from the leaves up, and assign each node a canonical id equal to the (deduplicated) sorted multiset of its children's ids, stored in a shared map across both trees. The trees are isomorphic iff their roots get the same canonical id.

用 AHU 规范标号：自叶向上处理，每个结点的规范 id 取其孩子 id 的有序多重集（在两棵树共享的映射中去重）。两树同构当且仅当其根的规范 id 相同。

## Complexity / 复杂度
$O(n\log n)$ over the sum of sizes. 关于规模之和 $O(n\log n)$。
