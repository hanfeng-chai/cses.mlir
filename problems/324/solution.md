# 324 - Filled Subgrid Count II

## Problem / 题目

Same setup as problem 323, but now count **rectangular** (not just square) monochromatic subgrids, for each letter.

设定与第 323 题相同，但这次要对每个字母统计**矩形**（不仅是正方形）单色子网格的个数。

## Idea / 思路

Counting *all* monochromatic rectangles is harder than squares because a rectangle's shape has two free parameters (height and width), so we cannot just track "the" best value per anchor — we need to count rectangles ending at every column, for every row, efficiently. The idea combines two classic techniques.

**Step 1 — turn each row into a histogram.** For row $i$, let $h[j]$ be the length of the vertical run of identical letters ending at $(i,j)$ (i.e. how many consecutive cells $g[i][j],g[i-1][j],\dots$ upward share the same letter). This is updated incrementally: $h[j]=h[j]+1$ if $g[i][j]=g[i-1][j]$, else $h[j]=1$.

**Step 2 — count rectangles with bottom row $i$ using "sum of subarray minimums".** Fix the bottom row $i$ and the right column $j$. A monochromatic rectangle with this bottom-right anchor is determined by picking a left column $l\le j$ (with all letters on row $i$ between $l$ and $j$ equal — we reset the computation whenever the letter changes horizontally) and a height $H$ with $1\le H\le \min(h[l],h[l+1],\dots,h[j])$: every such choice gives a distinct valid monochromatic rectangle (its top edge is $i-H+1$). So the number of rectangles anchored with right edge $j$ (and bottom row $i$) is
$$S_j=\sum_{l\le j}\min(h[l],\dots,h[j]).$$
This is exactly the well-known "sum of minimums of all subarrays ending at $j$" quantity, computable online with a monotone stack: keep a stack of (height, width) pairs; when a new $h[j]$ arrives, pop every stack entry with height $\ge h[j]$ (removing their contribution `height*width` from the running sum $S$, but keeping their combined width), then push $(h[j], \text{mergedWidth})$ and add $h[j]\cdot\text{mergedWidth}$ back to $S$. After this update $S$ equals $S_j$ exactly. We reset the stack and $S$ to empty whenever the letter changes horizontally within the row (since a rectangle cannot cross two different letters).

Adding $S_j$ to `cnt[letter]` for every row $i$ and column $j$ counts every monochromatic rectangle exactly once — by its own bottom row and right column, which are unique to it.

数所有的单色**矩形**比单色正方形更难，因为矩形有高和宽两个自由参数，不能只给每个锚点存一个"最优值"，而要能高效地对每一行、每一列都数出以它为右边界的矩形个数。做法结合了两个经典技巧。

**第一步——把每一行变成一个"直方图"。** 对第 $i$ 行，设 $h[j]$ 为以 $(i,j)$ 结尾、向上延伸的同字母竖直连续段长度（即 $g[i][j],g[i-1][j],\dots$ 往上有多少个连续同字母格子）。增量更新：若 $g[i][j]=g[i-1][j]$ 则 $h[j]=h[j]+1$，否则 $h[j]=1$。

**第二步——用"子数组最小值之和"数出以第 $i$ 行为底边的矩形。** 固定底行 $i$ 与右列 $j$。一个以此为右下角的单色矩形，由选定左列 $l\le j$（要求第 $i$ 行 $l$ 到 $j$ 之间字母都相同——一旦横向字母变化就重置计算）与高度 $H$（$1\le H\le \min(h[l],\dots,h[j])$）唯一确定：每一种选择都对应一个不同的合法单色矩形（其上边界为第 $i-H+1$ 行）。所以以右边界 $j$（底行 $i$）为锚的矩形个数是
$$S_j=\sum_{l\le j}\min(h[l],\dots,h[j])。$$
这正是著名的"以 $j$ 结尾的所有子数组最小值之和"，可以用单调栈在线维护：栈中存 (高度, 宽度) 对；新的 $h[j]$ 到来时，弹出所有高度 $\ge h[j]$ 的栈顶元素（把它们对 $S$ 的贡献 `height*width` 减掉，但把它们的宽度合并保留），然后压入 $(h[j], \text{合并宽度})$ 并把 $h[j]\cdot\text{合并宽度}$ 重新加回 $S$。更新后 $S$ 恰好等于 $S_j$。每当同一行内字母发生变化，就把栈和 $S$ 清空重置（矩形不能跨越两种不同字母）。

对每一行 $i$、每一列 $j$，把 $S_j$ 累加到 `cnt[该字母]` 上，就恰好不重不漏地数了每个单色矩形一次——因为矩形的底行与右列组合对它是唯一的。

## Complexity / 复杂度

$O(n^2)$ overall: each row does $O(n)$ work for the histogram update and $O(n)$ amortized work for the monotone-stack sum (each column pushed/popped once per row). With $n\le3000$ this is about $9\times10^6$ operations.

总体 $O(n^2)$：每行更新直方图 $O(n)$，单调栈求和均摊 $O(n)$（每列每行只入栈出栈一次）。$n\le3000$ 时约 $9\times10^6$ 次操作。
