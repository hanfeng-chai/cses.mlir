# 269 - Sliding Window Advertisement

## Problem / 题目
For each window of $k$ boards (a histogram), output the maximum-area axis-aligned rectangle that fits under the bars.

对每个 $k$ 块木板的窗口（一个直方图），输出可放入柱形下方的最大矩形面积。

## Idea / 思路
For each bar $i$ let $[A,B]$ be its maximal span where all bars are $\ge h_i$ (found with nearest-smaller stacks). Within a window starting at $w$, that bar yields a rectangle of width $\min(B,w+k-1)-\max(A,w)+1$, a piecewise-linear function of $w$ that rises, stays flat, then falls. Each piece is a line over a sub-range of $w$; insert all pieces into a Li Chao tree that supports range line insertion and maximum point queries. Querying each $w$ gives the largest rectangle of that window.

对每根柱 $i$，设 $[A,B]$ 为其所有柱 $\ge h_i$ 的最大跨度（用最近更小值栈求得）。在起点为 $w$ 的窗口中，该柱给出宽度 $\min(B,w+k-1)-\max(A,w)+1$ 的矩形，这是关于 $w$ 的分段线性函数（升、平、降）。每段是 $w$ 某子区间上的一条直线；把所有段插入支持区间插入与单点最大值查询的 Li Chao 树。对每个 $w$ 查询即得该窗口的最大矩形。

## Complexity / 复杂度
$O(n\log^2 n)$. $O(n\log^2 n)$。
