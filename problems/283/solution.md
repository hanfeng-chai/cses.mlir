# 283 - Xor Pyramid Diagonal

## Problem / 题目
Output the leftmost number of each row of the xor pyramid, from bottom to top.

输出 XOR 金字塔每行最左端的数，从底到顶。

## Idea / 思路
The leftmost number of row $r$ equals $\bigoplus_{i\subseteq r} a_i$ (by Lucas, $\binom{r}{i}$ is odd iff $i$ is a submask of $r$). Compute these submask-xor sums for all $r$ at once with a sum-over-subsets (SOS) DP.

第 $r$ 行最左数等于 $\bigoplus_{i\subseteq r} a_i$（由卢卡斯，$\binom{r}{i}$ 为奇当且仅当 $i$ 是 $r$ 的子掩码）。用子集和（SOS）DP 一次性算出所有 $r$ 的子掩码异或和。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
