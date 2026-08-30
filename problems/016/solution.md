# 016 - Apple Division

## Problem / 题目

There are $n \le 20$ apples with given weights. Split them into two groups so that the absolute difference of the two group weights is as small as possible.

有 $n \le 20$ 个苹果，重量已知。把它们分成两组，使两组重量之差的绝对值尽可能小。

## Idea / 思路

With $n \le 20$ there are at most $2^{20} \approx 10^6$ subsets, few enough to enumerate all of them. Treat each subset (a bitmask) as the first group; if its weight is $s$ and the total is $T$, the difference between the groups is $|T - 2s|$. Take the minimum of this value over all subsets.

由于 $n \le 20$，子集最多 $2^{20} \approx 10^6$ 个，可以全部枚举。把每个子集（一个位掩码）看作第一组；若其重量为 $s$、总重为 $T$，则两组之差为 $|T - 2s|$。在所有子集上取这个值的最小值即可。

## Complexity / 复杂度

We scan $2^n$ subsets and spend $O(n)$ summing each, giving $O(n \cdot 2^n)$ overall — about $2 \times 10^7$ operations for $n = 20$.

我们扫描 $2^n$ 个子集，每个用 $O(n)$ 求和，总计 $O(n \cdot 2^n)$ ——当 $n = 20$ 时约 $2 \times 10^7$ 次运算。
