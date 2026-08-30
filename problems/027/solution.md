# 027 - Ferris Wheel

## Problem / 题目

Each gondola holds at most two children and a total weight of at most $x$. Given the children's weights, find the minimum number of gondolas needed.

每个吊舱最多坐两个孩子、总重不超过 $x$。给定孩子们的体重，求所需吊舱的最少数量。

## Idea / 思路

Sort the weights and use two pointers, `lo` at the lightest and `hi` at the heaviest. The heaviest child must occupy a gondola; if the lightest remaining child also fits alongside ($p_{lo} + p_{hi} \le x$), seat them together and advance `lo`. Either way one gondola is used and `hi` moves inward. Pairing the heaviest with the lightest that fits is optimal.

把体重排序，用双指针 `lo` 指最轻、`hi` 指最重。最重的孩子必须占一个吊舱；若最轻的孩子也能一起坐下（$p_{lo} + p_{hi} \le x$），就让他们同舱并前移 `lo`。无论如何都用掉一个吊舱、`hi` 内移。让最重者与能拼上的最轻者同舱是最优的。

## Complexity / 复杂度

Sorting is the bottleneck, so the time is $O(n \log n)$.

排序是瓶颈，因此时间为 $O(n \log n)$。
