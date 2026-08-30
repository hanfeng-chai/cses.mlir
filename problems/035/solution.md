# 035 - Collecting Numbers

## Problem / 题目

An array contains each number $1 \dots n$ exactly once. In one round you scan left to right and collect numbers in increasing order as far as possible. How many rounds are needed to collect all numbers?

数组恰好包含每个数 $1 \dots n$ 各一次。每一轮你从左到右扫描，尽可能按递增顺序收集数。需要多少轮才能收集所有数？

## Idea / 思路

Record the position $pos[v]$ of each value. We can collect $v$ immediately after $v-1$ in the same round exactly when $v$ lies to the right of $v-1$, i.e. $pos[v] > pos[v-1]$. Every place where $pos[v] < pos[v-1]$ forces a new round. Hence the answer is $1$ plus the number of such "breakpoints".

记录每个值的位置 $pos[v]$。能在同一轮里紧接着 $v-1$ 收集 $v$，当且仅当 $v$ 在 $v-1$ 右侧，即 $pos[v] > pos[v-1]$。每出现一处 $pos[v] < pos[v-1]$ 就必须多开一轮。因此答案是 $1$ 加上这种"断点"的数量。

## Complexity / 复杂度

A single pass over the values gives $O(n)$.

对所有值单次遍历即可，为 $O(n)$。
