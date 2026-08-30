# 284 - Xor Pyramid Row

## Problem / 题目
Output the numbers on the $k$-th row from the top of the xor pyramid.

输出 XOR 金字塔从顶往下第 $k$ 行的所有数。

## Idea / 思路
The target row is the bottom row after applying the xor-reduction step $d=n-k$ times. Applying the step $2^t$ times has the closed form $b_j \mathrel{\oplus}= b_{j+2^t}$ (since only $\binom{2^t}{0}$ and $\binom{2^t}{2^t}$ are odd). So decompose $d$ into bits and, for each set bit $t$, perform $b_j \mathrel{\oplus}= b_{j+2^t}$ over the shrinking array.

目标行是底行执行 $d=n-k$ 次异或归约步后的结果。执行该步 $2^t$ 次有闭式 $b_j \mathrel{\oplus}= b_{j+2^t}$（因只有 $\binom{2^t}{0}$ 与 $\binom{2^t}{2^t}$ 为奇）。故把 $d$ 拆成二进制，对每个置位 $t$ 在收缩数组上做 $b_j \mathrel{\oplus}= b_{j+2^t}$。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
