# 191 - Stick Game

## Problem / 题目
A heap has $i$ sticks; a move removes $p\in P$ sticks; the player taking the last stick wins. For each $i=1..n$ print `W` if the first player wins, else `L`.

一堆有 $i$ 根棍；每步取走 $p\in P$ 根；取走最后一根者胜。对每个 $i=1..n$ 输出 `W`（先手胜）或 `L`。

## Idea / 思路
Game DP: position $i$ is winning iff some move $p\le i$ leads to a losing position $i-p$. With $\text{win}[0]=\text{false}$, fill $\text{win}[i]$ by scanning all allowed moves.

博弈 DP：位置 $i$ 为必胜当且仅当存在合法步 $p\le i$ 走到必败位置 $i-p$。以 $\text{win}[0]=\text{false}$ 为基，扫描所有合法步填 $\text{win}[i]$。

## Complexity / 复杂度
$O(nk)$. $O(nk)$。
