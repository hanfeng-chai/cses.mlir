# 111 - De Bruijn Sequence

## Problem / 题目

Construct a shortest binary string that contains every length-$n$ bit string as a substring.

构造一个最短的二进制串，使其包含每个长度为 $n$ 的比特串作为子串。

## Idea / 思路

Build the **De Bruijn graph**: nodes are the $2^{\,n-1}$ bit strings of length $n-1$, and each length-$n$ string is an edge from its $(n-1)$-prefix to its $(n-1)$-suffix, labelled by its last bit. An Eulerian circuit traverses all $2^n$ edges once; reading the edge labels along it, prefixed by the starting $(n-1)$ bits, yields a string of the minimal length $2^n + (n-1)$ that contains every length-$n$ substring. We find the circuit with Hierholzer's algorithm. Any valid sequence is accepted, so a problem-specific checker (`checker.cpp`) verifies the length and that all $2^n$ substrings appear.

构造 **De Bruijn 图**：节点是 $2^{\,n-1}$ 个长度 $n-1$ 的比特串，每个长度 $n$ 的串是一条从其 $(n-1)$-前缀到 $(n-1)$-后缀、以末位为标签的边。欧拉回路把全部 $2^n$ 条边各走一次；沿途读取边标签、并以起始 $(n-1)$ 位为前缀，即得长度最小为 $2^n + (n-1)$、包含每个长度 $n$ 子串的串。用 Hierholzer 算法求回路。任意合法序列都被接受，故题目专用 checker（`checker.cpp`）校验长度且全部 $2^n$ 个子串出现。

## Complexity / 复杂度

The graph has $2^n$ edges, so the time is $O(2^n)$.

图有 $2^n$ 条边，因此时间为 $O(2^n)$。
