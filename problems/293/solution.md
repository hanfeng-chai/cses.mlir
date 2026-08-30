# 293 - Filling Trominos

## Problem / 题目
Tile an $n\times m$ grid with L-trominoes, labeling cells so adjacent cells share a letter exactly when in the same tromino (or NO).

用 L 形三连块铺满 $n\times m$ 网格，给格子标字母使相邻格同字母当且仅当属于同一三连块（或 NO）。

## Idea / 思路
A tiling exists iff $3\mid nm$, $n,m\ge 2$, and neither $(n=3,m\text{ odd})$ nor $(m=3,n\text{ odd})$ holds. Tile mostly with $2\times3$ and $3\times2$ blocks; the only hard case is odd $\times$ odd, handled by a precomputed $5\times9$ (and transposed $9\times5$) seed plus $5\times6$/$6\times5$ strips. Finally color the trominoes greedily so adjacent ones get different letters, which enforces the "same letter iff same tromino" condition.

铺法存在当且仅当 $3\mid nm$、$n,m\ge 2$，且非 $(n=3,m\text{ 奇})$ 非 $(m=3,n\text{ 奇})$。大部分用 $2\times3$、$3\times2$ 条块铺；唯一困难是奇×奇，用预先求得的 $5\times9$（及转置 $9\times5$）种子加 $5\times6$/$6\times5$ 条块。最后对三连块贪心染色使相邻者字母不同，从而满足「同字母当且仅当同块」。

## Multi-solution / 多解
Any valid labeling is accepted; a custom checker verifies every same-letter region is an L-tromino.

任意合法标注均可；checker 验证每个同字母区域都是 L 形三连块。

## Complexity / 复杂度
$O(nm)$ per test. 每组 $O(nm)$。
