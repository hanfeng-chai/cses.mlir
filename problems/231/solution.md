# 231 - Lines and Queries II

## Problem / 题目
Process queries online: add a line $ax+b$ active on $[l,r]$, or ask the maximum value of any active line at $x$ (or `NO` if none).

在线处理询问：加入在 $[l,r]$ 上有效的直线 $ax+b$，或询问位置 $x$ 处有效直线的最大值（若无则 `NO`）。

## Idea / 思路
Use a Li Chao tree with range insertion: a line active on $[l,r]$ is inserted into the $O(\log X)$ canonical nodes covering that interval. A query walks the root-to-leaf path and takes the maximum; if only the sentinel is seen, no line is active and we print `NO`.

用支持区间插入的 Li Chao 树：在 $[l,r]$ 上有效的直线被插入到覆盖该区间的 $O(\log X)$ 个规范结点。查询沿根到叶路径取最大；若只见哨兵，则无有效直线，输出 `NO`。

## Complexity / 复杂度
$O(n\log^2 X)$. $O(n\log^2 X)$。
