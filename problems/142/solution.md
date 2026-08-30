# 142 - Range Queries and Copies

## Problem / 题目

Maintain a list of arrays (initially one). Support: set a value in array $k$, sum a range of array $k$, and append a copy of array $k$.

维护一个数组列表（初始一个）。支持：设置数组 $k$ 的某值、对数组 $k$ 求区间和、追加数组 $k$ 的副本。

## Idea / 思路

Use a **persistent segment tree**. Each array in the list is identified by a root pointer into a shared pool of nodes. A point update creates only the $O(\log n)$ new nodes along one root-to-leaf path, leaving all other versions untouched. Copying an array is $O(1)$: the new entry simply reuses the same root. Range-sum queries run on the chosen version's root.

使用**可持久化线段树**。列表中每个数组用指向共享节点池的根指针标识。单点更新只新建一条根到叶路径上的 $O(\log n)$ 个新节点，其余版本不受影响。复制数组是 $O(1)$：新条目直接复用同一个根。区间求和在所选版本的根上进行。

## Complexity / 复杂度

Each update and query is $O(\log n)$; a copy is $O(1)$.

每次更新与询问 $O(\log n)$；复制 $O(1)$。
