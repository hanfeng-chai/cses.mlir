# 193 - Nim Game II

## Problem / 题目
Like Nim, but each move removes $1$, $2$, or $3$ sticks from one heap; last to move wins. Decide the winner.

类似 Nim，但每步从某一堆取 $1$、$2$ 或 $3$ 根；取走最后一根者胜。判断胜者。

## Idea / 思路
A single heap of size $x$ under the subtraction set $\{1,2,3\}$ has Grundy value $x\bmod 4$. By Sprague–Grundy the game is a first-player win iff the XOR of $x_i\bmod 4$ over all heaps is non-zero.

减法集 $\{1,2,3\}$ 下，单堆大小 $x$ 的 Grundy 值为 $x\bmod 4$。由 Sprague–Grundy，先手胜当且仅当所有堆 $x_i\bmod 4$ 的异或非零。

## Complexity / 复杂度
$O(n)$ per test. 每组 $O(n)$。
