# 249 - Houses and Schools

## Problem / 题目
Place $k$ schools among $n$ houses on a line so the total walking distance of all children (each going to the nearest school) is minimized.

在一条直线上的 $n$ 座房子中设立 $k$ 所学校，使所有孩子（各去最近学校）的总步行距离最小。

## Idea / 思路
Let $\text{cost}(a,b)$ be the optimal one-school cost for houses $a..b$ (the school is placed at the weighted median). All these costs are precomputed in $O(n^2)$ by extending the right endpoint and shifting the weighted median incrementally. Then $dp_j[i]=\min_p\big(dp_{j-1}[p]+\text{cost}(p+1,i)\big)$ is solved with divide-and-conquer optimization, since the cost satisfies the quadrangle inequality (so the optimal split point is monotonic).

设 $\text{cost}(a,b)$ 为房子 $a..b$ 用一所学校的最优代价（学校设在加权中位数处）。这些代价通过右端点扩张并增量移动加权中位数在 $O(n^2)$ 内预处理。随后 $dp_j[i]=\min_p\big(dp_{j-1}[p]+\text{cost}(p+1,i)\big)$ 用分治优化求解，因代价满足四边形不等式（最优分割点单调）。

## Complexity / 复杂度
$O(n^2 + nk\log n)$. $O(n^2 + nk\log n)$。
