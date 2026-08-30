# 205 - Palindrome Queries

## Problem / 题目
Maintain a string under two operations: change a character, and test whether a substring $[a,b]$ is a palindrome ($n,m\le 2\cdot10^5$).

在两种操作下维护字符串：修改某字符；查询子串 $[a,b]$ 是否为回文（$n,m\le 2\cdot10^5$）。

## Idea / 思路
Keep polynomial hashes in Fenwick trees: a forward hash where position $i$ carries weight $p^{i}$, and a reverse hash where it carries weight $p^{n-1-i}$. The substring is a palindrome iff its forward hash equals its reverse hash (after normalizing by the appropriate power of $p$). A character change is a point update on both trees. Two independent moduli are used to make collisions negligible.

用树状数组维护多项式哈希：正向哈希中位置 $i$ 的权为 $p^{i}$，反向哈希中权为 $p^{n-1-i}$。子串为回文当且仅当其正向哈希等于反向哈希（各自除以适当的 $p$ 幂归一化后）。修改字符即对两棵树做单点更新。使用两个独立模数使碰撞概率可忽略。

## Complexity / 复杂度
$O((n+m)\log n)$. $O((n+m)\log n)$。
