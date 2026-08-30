# 308 - Network Breakdown

## Problem / 题目
Edges break one by one; after each breakdown output the number of connected components.

边逐条断开；每次断开后输出连通分量数。

## Idea / 思路
Process offline in reverse. Start from the final graph (all edges except the broken ones) and union them to get the initial component count. Then re-add the broken edges in reverse order: record the current count before each re-addition, and decrement when a union merges two components. Output the recorded counts in forward order.

离线倒序处理。先从最终图（除被断边外的所有边）合并得初始分量数，再按逆序重新加入被断的边：每次加入前记录当前分量数，合并两分量时减一。最后按正序输出记录值。

## Complexity / 复杂度
$O((n+m)\alpha(n))$. $O((n+m)\alpha(n))$。
