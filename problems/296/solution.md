# 296 - Prüfer Code

## Problem / 题目
Reconstruct a tree on $n$ nodes from its Prüfer code of length $n-2$.

由长度 $n-2$ 的 Prüfer 序列重建 $n$ 个结点的树。

## Idea / 思路
Set every node's degree to $1$ plus its count in the code. Repeatedly take the smallest-labelled current leaf, connect it to the next code value, and decrease that node's degree (using a linear pointer that only moves forward). Finally connect the last remaining leaf to node $n$.

每个结点的度设为 $1$ 加其在序列中的出现次数。反复取当前最小标号的叶子，与下一个序列值连边并将该值的度减一（用只前进的线性指针）。最后把剩下的叶子与结点 $n$ 连边。

## Multi-solution / 多解
The tree is unique, but edges may be printed in any order/orientation; the checker re-encodes the output tree's Prüfer code and compares it to the input.

树唯一，但边的顺序与端点次序任意；checker 对输出的树重新求 Prüfer 序列并与输入比对。

## Complexity / 复杂度
$O(n)$. $O(n)$。
