# 103 - Planets Cycles

## Problem / 题目

Each of $n$ planets has one outgoing teleporter. Starting from each planet and following teleporters until you reach an already-visited planet, report how many teleportations that takes.

$n$ 颗行星每颗有一个出向传送门。从每颗行星出发跟随传送，直到到达一个已访问过的行星，报告这需要多少次传送。

## Idea / 思路

In a functional graph the walk from any planet runs down a tree tail and then enters a cycle; the first repeat happens exactly when you come back to the cycle node you entered, after going once around the cycle. So the answer for planet $v$ is $depth[v] + (\text{length of the cycle it enters})$, where $depth[v]$ is the number of steps from $v$ to the cycle (and $0$ for cycle planets). We decompose the graph into cycles and tree depths once, then output the sum for each planet.

在函数图中，从任意行星出发的行走先沿树尾下降再进入环；第一次重复恰好发生在绕环一圈回到入环节点时。因此行星 $v$ 的答案为 $depth[v] + (\text{它进入的环的长度})$，其中 $depth[v]$ 是 $v$ 到环的步数（环上行星为 $0$）。我们一次性把图分解成环与树深度，再对每颗行星输出该和。

## Complexity / 复杂度

The decomposition and answers take $O(n)$.

分解与作答均为 $O(n)$。
