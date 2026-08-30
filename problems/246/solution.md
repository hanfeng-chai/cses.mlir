# 246 - Monster Game I

## Problem / 题目
Kill a subset of monsters (the last one mandatory) to win. Killing monster $i$ costs $s_i\cdot f$ where $f$ is the current skill factor, and afterwards the factor becomes $f_i$. Minimize the total time. Here $s$ is increasing and $f$ is decreasing.

击杀部分怪物（最后一只必杀）以获胜。击杀怪物 $i$ 花费 $s_i\cdot f$（$f$ 为当前技能系数），之后系数变为 $f_i$。最小化总时间。此处 $s$ 递增、$f$ 递减。

## Idea / 思路
Let $dp_i$ be the minimum time to have just killed monster $i$. Then $dp_i=\min_j (dp_j+s_i\cdot f_j)$ over the previous kill $j$ (or the start with factor $x$). Each candidate is a line $y=f_j\cdot s+dp_j$ evaluated at $s=s_i$, so the convex hull trick (here via a Li Chao tree) finds the minimum; insert monster $i$'s line after computing $dp_i$. The answer is $dp_n$.

设 $dp_i$ 为刚击杀怪物 $i$ 的最小时间。则 $dp_i=\min_j (dp_j+s_i\cdot f_j)$，$j$ 为上一次击杀（或系数 $x$ 的起点）。每个候选是直线 $y=f_j\cdot s+dp_j$ 在 $s=s_i$ 处取值，故用凸包优化（此处用 Li Chao 树）求最小；算出 $dp_i$ 后插入怪物 $i$ 的直线。答案为 $dp_n$。

## Complexity / 复杂度
$O(n\log V)$. $O(n\log V)$。
