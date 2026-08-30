# 174 - Permutation Order

## Problem / 题目
Two query types on permutations of $1..n$ ($n\le 20$): type 1 asks for the $k$-th permutation in lexicographic order; type 2 asks for the lexicographic rank of a given permutation.

对 $1..n$ 排列（$n\le 20$）的两类询问：类型 1 求字典序第 $k$ 个排列；类型 2 求给定排列的字典序排名。

## Idea / 思路
Use the factorial number system. For type 1, repeatedly pick index $\lfloor k/(n-1-i)!\rfloor$ from the remaining available values and reduce $k$ modulo that factorial. For type 2, sum over positions the count of smaller still-unused values times the corresponding factorial, plus one. With $n\le 20$, $20!$ fits in a 64-bit integer, so no modulo is needed.

使用阶乘进制。类型 1：每步从剩余可用值中取下标 $\lfloor k/(n-1-i)!\rfloor$，并令 $k$ 对该阶乘取模。类型 2：对每个位置累加「后面更小且未用值的个数 $\times$ 相应阶乘」，最后加一。因 $n\le 20$，$20!$ 可用 64 位整型表示，无需取模。

## Complexity / 复杂度
$O(n^2)$ per query. 每询问 $O(n^2)$。
