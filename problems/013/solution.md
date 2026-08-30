# 013 - Gray Code

## Problem / 题目

Print a Gray code of length $n$: a list of all $2^n$ bit strings of length $n$ such that any two consecutive strings (and the last and first) differ in exactly one bit.

输出长度为 $n$ 的格雷码：列出所有 $2^n$ 个长度为 $n$ 的二进制串，使得任意相邻两个串（以及首尾两个）恰好只有一位不同。

## Idea / 思路

The standard **reflected Gray code** maps the integer $i$ to $i \oplus (i \gg 1)$ (XOR of $i$ with $i$ shifted right by one). As $i$ runs from $0$ to $2^n - 1$, printing this value in $n$ bits produces a valid Gray code, because incrementing $i$ by one flips exactly one bit of $i \oplus (i \gg 1)$. Since the judge accepts **any** valid Gray code, we ship a problem-specific checker (`checker.cpp`) that verifies all strings are distinct, of the right length, and that neighbours differ in one bit.

标准的**反射格雷码**把整数 $i$ 映射为 $i \oplus (i \gg 1)$（$i$ 与右移一位后的 $i$ 异或）。当 $i$ 从 $0$ 取到 $2^n - 1$，把这个值按 $n$ 位输出就得到一个合法格雷码，因为 $i$ 每加一恰好会翻转 $i \oplus (i \gg 1)$ 的一位。由于评测接受**任意**合法格雷码，我们提供题目专用 checker（`checker.cpp`），校验所有串互不相同、长度正确、且相邻串只差一位。

## Complexity / 复杂度

There are $2^n$ lines and each needs $n$ characters, so output and time are $O(n \cdot 2^n)$.

共 $2^n$ 行、每行 $n$ 个字符，因此输出与时间均为 $O(n \cdot 2^n)$。
