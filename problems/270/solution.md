# 270 - Hidden Integer

## Problem / 题目
Find a hidden integer $x\in[1,10^9]$ using at most $30$ queries of the form "is $y<x$?".

用至多 $30$ 次「$y<x$ 吗？」的询问找出隐藏整数 $x\in[1,10^9]$。

## Idea / 思路
Binary search. Maintain a candidate range $[\text{lo},\text{hi}]$; query the midpoint $y$. A `YES` ($y<x$) moves $\text{lo}$ to $y+1$, a `NO` moves $\text{hi}$ to $y$. The range halves each step, needing $\lceil\log_2 10^9\rceil=30$ queries. Flush after every output.

二分查找。维护候选区间 $[\text{lo},\text{hi}]$，询问中点 $y$。`YES`（$y<x$）令 $\text{lo}=y+1$，`NO` 令 $\text{hi}=y$。每步区间减半，共需 $\lceil\log_2 10^9\rceil=30$ 次。每次输出后刷新缓冲。

## Complexity / 复杂度
$30$ queries. $30$ 次询问。
