# 247 - Monster Game II

## Problem / 题目
Same as Monster Game I, but the strengths $s_i$ and skill factors $f_i$ are not monotonic.

与 Monster Game I 相同，但强度 $s_i$ 与技能系数 $f_i$ 不单调。

## Idea / 思路
The DP recurrence is identical, $dp_i=\min_j (dp_j+s_i\cdot f_j)$, but without monotonicity the lines have arbitrary slopes and the queries are in arbitrary order. A Li Chao tree over the domain of possible strengths supports inserting arbitrary lines and answering minimum queries, so the same approach works.

DP 递推相同，$dp_i=\min_j (dp_j+s_i\cdot f_j)$，但失去单调性后直线斜率任意、查询次序任意。在强度取值域上的 Li Chao 树支持插入任意直线并回答最小值查询，故同法可行。

## Complexity / 复杂度
$O(n\log V)$. $O(n\log V)$。
