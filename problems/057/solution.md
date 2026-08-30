# 057 - Array Division

## Problem / 题目

Split a positive-integer array into $k$ contiguous subarrays, minimising the largest subarray sum.

把一个正整数数组分成 $k$ 段连续子数组，使最大的子数组和尽可能小。

## Idea / 思路

Binary search the answer $S$ — the largest sum any part is allowed to have. A greedy left-to-right pass counts the minimum number of parts needed when no part may exceed $S$: keep adding to the current part and start a new one whenever the next value would overflow. Feasibility (parts $\le k$) is monotone in $S$, so binary-search the smallest feasible $S$. The search's lower bound is the largest single element.

二分答案 $S$ ——允许任何一段达到的最大和。一次从左到右的贪心扫描统计在每段不超过 $S$ 时所需的最少段数：不断把元素加进当前段，一旦加入下一个会超过 $S$ 就另起一段。可行性（段数 $\le k$）关于 $S$ 单调，于是二分最小可行的 $S$。二分的下界是最大的单个元素。

## Complexity / 复杂度

Each feasibility check is $O(n)$, so the total is $O(n \log(\text{sum}))$.

每次可行性检查为 $O(n)$，因此总计 $O(n \log(\text{总和}))$。
