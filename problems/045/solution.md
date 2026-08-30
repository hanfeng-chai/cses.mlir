# 045 - Nested Ranges Count

## Problem / 题目

For each of $n$ ranges, count how many other ranges it contains and how many other ranges contain it.

对 $n$ 个区间中的每一个，统计它包含多少个其他区间、以及有多少个其他区间包含它。

## Idea / 思路

Sort the ranges by $x$ ascending (ties by $y$ descending) and coordinate-compress the $y$ values. Sweeping forward, the number of ranges that **contain** range $i$ equals how many already-inserted endpoints have $y' \ge y_i$ (those automatically have $x' \le x_i$). Sweeping backward, the number of ranges **contained by** $i$ equals how many inserted endpoints have $y' \le y_i$ (those have $x' \ge x_i$). A Fenwick tree over the compressed $y$ answers each count in logarithmic time.

把区间按 $x$ 升序（$x$ 相同则 $y$ 降序）排序，并对 $y$ 值做坐标压缩。正向扫描时，**包含**区间 $i$ 的区间数等于已插入端点中 $y' \ge y_i$ 的个数（它们自然满足 $x' \le x_i$）。反向扫描时，被 $i$ **包含**的区间数等于已插入端点中 $y' \le y_i$ 的个数（它们满足 $x' \ge x_i$）。用一棵建立在压缩 $y$ 上的树状数组即可在对数时间内回答每个计数。

## Complexity / 复杂度

Sorting and $n$ Fenwick operations give $O(n \log n)$.

排序加 $n$ 次树状数组操作，为 $O(n \log n)$。
