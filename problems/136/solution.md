# 136 - Distinct Values Queries II

## Problem / 题目

Process queries: update a value, or check whether every value in a range $[a,b]$ is distinct.

处理询问：更新一个值，或检查区间 $[a,b]$ 内的值是否互不相同。

## Idea / 思路

For each position $i$ keep $\text{nxt}[i]$ = the next position with the same value (or $\infty$). The range $[a,b]$ has all distinct values **iff** $\min_{i\in[a,b]} \text{nxt}[i] > b$ (no duplicate falls inside). We store the values' positions in a sorted set per value and keep $\text{nxt}$ in a segment tree of minimums. An update at $k$ removes $k$ from its old value's set (fixing the predecessor's $\text{nxt}$) and inserts it into the new value's set (fixing the new neighbours), touching only a few $\text{nxt}$ entries.

对每个位置 $i$ 记 $\text{nxt}[i]$ = 下一个同值位置（或 $\infty$）。区间 $[a,b]$ 全不同**当且仅当** $\min_{i\in[a,b]} \text{nxt}[i] > b$（没有重复落在内部）。我们为每个值用有序集合存其位置，并用最小值线段树维护 $\text{nxt}$。在 $k$ 处更新时，把 $k$ 从旧值集合移除（修正前驱的 $\text{nxt}$）、插入新值集合（修正新邻居），只改动少数 $\text{nxt}$ 项。

## Complexity / 复杂度

Each operation is $O(\log n)$.

每个操作 $O(\log n)$。
