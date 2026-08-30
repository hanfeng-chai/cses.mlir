# 214 - String Transform

## Problem / 题目
Invert the Burrows–Wheeler transform: given the transformed string of length $n+1$ (containing a sentinel `#`), recover the original string of length $n$.

求 Burrows–Wheeler 变换的逆：给定长度 $n+1$ 的变换串（含哨兵 `#`），还原长度 $n$ 的原串。

## Idea / 思路
The input is the last column $L$ of the sorted rotation matrix. Build the LF-mapping: $\text{LF}(i)=\text{start}[L_i]+\text{rank of }i\text{ among equal characters}$, where $\text{start}[c]$ counts characters smaller than $c$. Starting at the row containing `#` and repeatedly applying $\text{LF}$ while collecting characters yields the rotation; reversing it gives `#` followed by the original string, so we drop the leading `#`.

输入是排序后旋转矩阵的最后一列 $L$。构造 LF 映射：$\text{LF}(i)=\text{start}[L_i]+i\text{ 在相同字符中的名次}$，其中 $\text{start}[c]$ 为小于 $c$ 的字符数。从含 `#` 的行出发反复应用 $\text{LF}$ 并收集字符得到旋转串；将其反转即为「`#` + 原串」，去掉开头的 `#` 即原串。

## Complexity / 复杂度
$O(n)$. $O(n)$。
