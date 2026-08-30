# 359 - Maximum Average Subarrays

## Problem / 题目

For every $i=1,\dots,n$, find the length of the subarray ending at $i$ with the maximum average (breaking ties by choosing the longest such subarray).

对每个 $i=1,\dots,n$，求以 $i$ 结尾、平均值最大的子数组长度（若有并列，取最长的那个）。

## Idea / 思路

Let $S$ be the prefix-sum array. The average of $x_{l..i}$ is $\dfrac{S_i-S_{l-1}}{i-(l-1)}$ — exactly the **slope** of the line connecting the two points $(l-1,\,S_{l-1})$ and $(i,\,S_i)$ on the "prefix-sum plot". So maximizing the average over choices of $l\le i$ is the same as, among all points $(j,S_j)$ for $j<i$, finding the one with the maximum slope to the fixed point $(i,S_i)$ — a classic **convex hull trick** setup.

Maintain the **lower convex hull** of the points $(0,S_0),(1,S_1),\dots$ incrementally as $i$ grows (adding point $(i-1,S_{i-1})$ right before answering query $i$): when adding a new point, pop hull points from the back while they are no longer below the line to the new point (using `>=` rather than `>` in the pop test, so that collinear points collapse down to just the two extremes — this is exactly what makes ties resolve toward the **leftmost** point later, i.e. the longest subarray).

For query $i$, the "slope to $(i,S_i)$" as a function of position along the hull is unimodal (rises then falls), so a **binary search comparing adjacent hull points** (`is f(mid) < f(mid+1)`, using cross-multiplication to avoid floating point) finds the maximizer in $O(\log n)$; using a strict `<` in the comparator makes the search settle on the *smallest* index among tied maxima, again favoring the longest subarray.

设 $S$ 为前缀和数组。$x_{l..i}$ 的平均值是 $\dfrac{S_i-S_{l-1}}{i-(l-1)}$——这正是"前缀和折线图"上两点 $(l-1,\,S_{l-1})$ 与 $(i,\,S_i)$ 连线的**斜率**。所以在 $l\le i$ 上最大化平均值，就等价于：在所有点 $(j,S_j)$（$j<i$）中找到与固定点 $(i,S_i)$ 连线斜率最大的那个——这是经典的**凸包优化（convex hull trick）**场景。

随着 $i$ 增大，增量维护点集 $(0,S_0),(1,S_1),\dots$ 的**下凸包**（在回答第 $i$ 个询问之前，先加入点 $(i-1,S_{i-1})$）：加入新点时，只要栈顶的点不再处于"到新点连线"的下方，就从后往前弹出（用 `>=` 而不是 `>` 做弹出判断，这样共线的点会被压缩到只剩两端——这正是让并列情况之后偏向**最左**点、也就是最长子数组的关键）。

对于询问 $i$，"到 $(i,S_i)$ 的斜率"作为凸包上位置的函数是单峰的（先升后降），所以用**比较相邻凸包点的二分**（判断 `f(mid) < f(mid+1)`，用交叉相乘避免浮点误差）就能在 $O(\log n)$ 内找到最大值点；比较符用严格的 `<`，会让二分停在并列最大值中**下标最小**的那个，同样偏向最长子数组。

## Complexity / 复杂度

Maintaining the hull is $O(n)$ amortized (each point pushed/popped once). Each of the $n$ queries does an $O(\log n)$ binary search on the hull. Overall $O(n\log n)$.

维护凸包均摊 $O(n)$（每个点只入栈出栈一次）。$n$ 次询问每次在凸包上做 $O(\log n)$ 二分。总体 $O(n\log n)$。
