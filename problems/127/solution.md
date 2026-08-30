# 127 - List Removals

## Problem / 题目

Given a list, repeatedly remove the element at a given current position and report it.

给定一个列表，反复移除给定当前位置的元素并报告它。

## Idea / 思路

Keep a Fenwick tree where position $i$ holds $1$ if the original element is still present. The "$p$-th remaining element" is the smallest index whose prefix count equals $p$, found by a **binary search on the Fenwick tree** (descending the implicit binary structure). After reporting that element, set its slot to $0$ so later positions shift automatically.

用一个树状数组，位置 $i$ 为 $1$ 表示原元素仍在。"第 $p$ 个剩余元素"是前缀计数等于 $p$ 的最小下标，用**树状数组上的二分**（沿其隐含二进制结构下降）找到。报告后把该槽置 $0$，后续位置自动顺移。

## Complexity / 复杂度

Each removal is $O(\log n)$.

每次移除 $O(\log n)$。
