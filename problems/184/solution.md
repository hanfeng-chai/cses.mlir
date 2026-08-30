# 184 - System of Linear Equations

## Problem / 题目
Solve $n$ linear equations in $m$ variables over $\mathbb{Z}_{10^9+7}$ ($n,m\le 500$). Output any valid solution, or $-1$ if none exists.

在模 $10^9+7$ 域上求解 $n$ 个方程、$m$ 个未知数的线性方程组（$n,m\le 500$）。输出任意一组合法解，无解则 $-1$。

## Idea / 思路
Run Gauss–Jordan elimination modulo the prime to reduced row echelon form, using modular inverses for pivots. After elimination, if any all-zero coefficient row has a nonzero right-hand side the system is inconsistent ($-1$). Otherwise set free variables to $0$, so each pivot variable equals its row's right-hand side.

对该质数做高斯—约旦消元到行最简形，主元处用模逆元。消元后若存在系数全零但右端非零的行，则方程组矛盾（$-1$）。否则令自由变量取 $0$，则每个主元变量等于其所在行的右端值。

## Multi-solution / 多解
Any valid assignment is accepted, so a custom checker verifies the range $0\le x_i<p$ and that every equation holds modulo $p$ (and that "$-1$" is reported only when the jury also finds no solution).

任意合法解均可接受，故自定义 checker 验证范围 $0\le x_i<p$ 且每个方程模 $p$ 成立（并要求仅当标程也判无解时才接受 "$-1$"）。

## Complexity / 复杂度
$O(nm\cdot\min(n,m))$. $O(nm\cdot\min(n,m))$。
