# 069 - Edit Distance

## Problem / 题目

Compute the edit distance between two strings: the minimum number of single-character insertions, deletions, and replacements to turn one string into the other.

计算两个字符串的编辑距离：把一个串变成另一个串所需的最少单字符插入、删除、替换次数。

## Idea / 思路

Let $dp[i][j]$ be the edit distance between the first $i$ characters of $a$ and the first $j$ of $b$. The transitions are $dp[i][j] = \min(dp[i-1][j]+1,\; dp[i][j-1]+1,\; dp[i-1][j-1]+[a_i \ne b_j])$, corresponding to delete, insert, and match/replace. Base cases $dp[i][0]=i$ and $dp[0][j]=j$. Since each row depends only on the previous one, we keep two rolling rows.

设 $dp[i][j]$ 为 $a$ 的前 $i$ 个字符与 $b$ 的前 $j$ 个字符之间的编辑距离。转移为 $dp[i][j] = \min(dp[i-1][j]+1,\; dp[i][j-1]+1,\; dp[i-1][j-1]+[a_i \ne b_j])$，分别对应删除、插入、匹配/替换。边界 $dp[i][0]=i$、$dp[0][j]=j$。由于每行只依赖上一行，我们用两行滚动数组。

## Complexity / 复杂度

There are $nm$ states each computed in constant time, so the time is $O(nm)$ with $O(m)$ memory.

共 $nm$ 个状态、每个常数时间，因此时间 $O(nm)$、空间 $O(m)$。
