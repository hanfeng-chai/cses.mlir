# 274 - Colored Chairs

## Problem / 题目
$n$ chairs (odd $n$) in a circle are red or blue. Find two adjacent chairs of the same color using at most $20$ color queries.

环形排列的 $n$（奇数）把椅子非红即蓝。用至多 $20$ 次颜色询问，找出相邻同色的两把椅子。

## Idea / 思路
Since $n$ is odd, the circle cannot be perfectly 2-colored, so an adjacent same-color pair must exist. Query chairs $1$ and $n$. If they match, chairs $n$ and $1$ are the answer. Otherwise define the mismatch $m(i)$ between chair $i$'s color and a perfect alternation from chair $1$; $m$ flips exactly at a same-color edge. With $m(1)=0$ and $m(n)=1$, binary search for an index where $m$ flips, which is an adjacent same-color pair.

由于 $n$ 为奇数，环无法完美二染色，必存在相邻同色对。询问椅子 $1$ 与 $n$。若同色，则椅子 $n$ 与 $1$ 即答案。否则定义椅 $i$ 颜色与「从椅 $1$ 起完美交替」的不一致 $m(i)$；$m$ 恰在同色边处翻转。由 $m(1)=0$、$m(n)=1$，二分找 $m$ 翻转处，即相邻同色对。

## Complexity / 复杂度
$O(\log n)$ queries. $O(\log n)$ 次询问。
