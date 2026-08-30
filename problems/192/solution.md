# 192 - Nim Game I

## Problem / 题目
Standard Nim: $n$ heaps; a move removes any positive number of sticks from one heap; last to move wins. Decide the winner.

标准 Nim：$n$ 堆；每步从某一堆取任意正数根；取走最后一根者胜。判断胜者。

## Idea / 思路
By the Sprague–Grundy / Bouton theorem, the first player wins iff the XOR of all heap sizes is non-zero.

由 Sprague–Grundy / Bouton 定理，先手胜当且仅当所有堆大小的异或非零。

## Complexity / 复杂度
$O(n)$ per test. 每组 $O(n)$。
