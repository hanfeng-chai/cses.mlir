# 395 - Mex Grid Queries

## Problem / 题目

In a grid where every square holds the smallest nonnegative integer not appearing earlier in its row or above in its column, find the value at square $(y,x)$.

网格每个格子的值是"该行左侧和该列上方都没出现过的最小非负整数"，求 $(y,x)$ 处的值。

## Idea / 思路

Computing this recursive definition for a small grid by brute force reveals a clean closed form: using 0-indexed coordinates, the value at $(y,x)$ is simply $y\oplus x$ (bitwise XOR). E.g. row $y=2$ (0-indexed) starts $2,3,0,1,6,7,4,5,10,11,\dots = 2{\oplus}0,2{\oplus}1,2{\oplus}2,2{\oplus}3,\dots$

*Why XOR works:* fix a row $y$. As $x$ ranges over $0,1,2,\dots$, the values $y\oplus x$ run through **every** nonnegative integer exactly once (XOR with a fixed $y$ is a bijection on $\{0,1,2,\dots\}$), so among the first $x$ entries of the row, the set of values present is *not* simply $\{0,\dots,x-1\}$ in general — but the key fact is subtler and is really about a **Latin-square / group-table** property: for any two DIFFERENT rows $y_1\ne y_2$ and any column $x$, the values $y_1\oplus x$ and $y_2\oplus x$ are different (since XOR is injective in the first argument for fixed second argument), and symmetric for columns. This means the grid formed by $y\oplus x$ satisfies exactly the requirement that is used to *inductively verify* the mex definition: assuming $y\oplus x$ is correct for all smaller-index cells (by strong induction on $y+x$ or the recursive order), the set $\{y\oplus x' : x'<x\}\cup\{y'\oplus x : y'<y\}$ never contains $y\oplus x$ itself (since XOR is injective) but *does* contain every value strictly smaller than $y\oplus x$ that could possibly be "missing" — this is the standard "Nim-value / Sprague–Grundy" identity that $y\oplus x$ is exactly the mex of the row/column prefixes, a well-known combinatorial-game-theory fact (the same reason Nim's P-positions are characterized by XOR).

*Sanity check* on the sample: $1$-indexed $(y,x)=(3,5)$ becomes $0$-indexed $(2,4)$; $2\oplus4=6$, matching the expected output.

对这个递归定义暴力算一个小网格，会发现一个干净的封闭形式：用0索引坐标，$(y,x)$ 处的值就是 $y\oplus x$（按位异或）。例如第 $y=2$ 行（0索引）开头是 $2,3,0,1,6,7,4,5,10,11,\dots=2{\oplus}0,2{\oplus}1,2{\oplus}2,\dots$

*为什么是异或：* 固定行 $y$，当 $x$ 取遍 $0,1,2,\dots$ 时，$y\oplus x$ 恰好不重复地取遍**每个**非负整数（固定 $y$ 后异或是 $\{0,1,2,\dots\}$ 上的一个双射）。真正的关键事实更微妙，它其实是一个**拉丁方/群表**性质：对任意两个不同的行 $y_1\ne y_2$ 和任意列 $x$，$y_1\oplus x$ 与 $y_2\oplus x$ 一定不同（固定第二个参数时异或对第一个参数是单射），对列也对称。这正好满足用来**归纳验证** mex 定义所需的条件：假设对所有"更早"的格子 $y\oplus x$ 已经正确（按 $y+x$ 或递归顺序做强归纳），集合 $\{y\oplus x' : x'<x\}\cup\{y'\oplus x : y'<y\}$ 不可能包含 $y\oplus x$ 本身（异或的单射性），但确实包含所有严格小于 $y\oplus x$ 的、原本"可能缺失"的值——这正是组合游戏论中"Nim 值 / Sprague–Grundy"的经典恒等式（Nim 游戏的必败态由异或刻画，本质同源）。

*样例验证：* 1索引的 $(y,x)=(3,5)$ 对应0索引 $(2,4)$；$2\oplus4=6$，与期望输出一致。

## Complexity / 复杂度

$O(1)$ per query.

每次查询 $O(1)$。
