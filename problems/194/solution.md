# 194 - Stair Game

## Problem / 题目
Stairs $1..n$ hold balls. A move takes any number of balls from a stair $k\neq 1$ down to stair $k-1$; last to move wins. Decide the winner.

楼梯 $1..n$ 上各有若干球。每步把某级 $k\neq 1$ 上任意数量的球移到第 $k-1$ 级；最后行动者胜。判断胜者。

## Idea / 思路
This is staircase Nim. Balls at an even distance from the ground (stair $1$) can be "mirrored" and do not matter; the game reduces to ordinary Nim on the balls at odd distance, i.e. on the even-indexed stairs $2,4,6,\dots$. The first player wins iff the XOR of balls on the even-indexed stairs is non-zero.

这是阶梯 Nim。距地面（第 $1$ 级）偶数距离的球可被「镜像」抵消、无关紧要；游戏归约为奇数距离上球的普通 Nim，即偶数编号楼梯 $2,4,6,\dots$ 上的球。先手胜当且仅当偶数编号楼梯上球数的异或非零。

## Complexity / 复杂度
$O(n)$ per test. 每组 $O(n)$。
