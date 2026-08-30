# 043 - Josephus Problem II

## Problem / 题目

$n$ children stand in a circle. Repeatedly skip $k$ children and remove the next, until none remain. Output the order of removal. Here $k$ can be very large.

$n$ 个孩子站成一圈。反复跳过 $k$ 个、移除下一个，直到无人剩下。输出移除顺序。这里 $k$ 可能很大。

## Idea / 思路

A naive queue costs $O(k)$ per removal, too slow. Instead keep a Fenwick (BIT) tree marking which children are still present. At each step the victim sits at order-index $(\text{pos} + k) \bmod \text{remaining}$ among the survivors; we find that survivor by binary-searching the Fenwick prefix sums (the smallest index whose prefix count reaches the target), output it, and mark it removed.

朴素队列每次移除花费 $O(k)$，太慢。改用 Fenwick（树状数组）标记哪些孩子仍在场。每一步受害者位于幸存者中的顺序下标 $(\text{pos} + k) \bmod \text{remaining}$；我们对 Fenwick 前缀和做二分（找前缀计数首次达到目标的最小下标）来定位该幸存者，输出并标记移除。

## Complexity / 复杂度

Each of the $n$ removals does an $O(\log n)$ Fenwick search, so the total is $O(n \log n)$.

$n$ 次移除每次做一次 $O(\log n)$ 的 Fenwick 二分，因此总计 $O(n \log n)$。
