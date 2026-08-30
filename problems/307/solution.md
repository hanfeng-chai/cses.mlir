# 307 - MST Edge Cost

## Problem / 题目
For each edge output the minimum spanning tree cost given that this edge **must** be included.

对每条边，输出强制包含它时的最小生成树代价。

## Idea / 思路
Compute one MST and its total weight $W$. If an edge is in the MST the answer is $W$. Otherwise forcing edge $(u,v,w)$ in creates a cycle; remove the heaviest edge on the MST path between $u$ and $v$, giving $W - \max\text{-on-path}(u,v) + w$. The maximum edge on a tree path is found with binary-lifting LCA storing path maxima.

求一棵 MST 及总权 $W$。若边在 MST 中答案为 $W$；否则强制 $(u,v,w)$ 成环，删去 MST 上 $u,v$ 路径的最重边，得 $W-\max\text{路径}(u,v)+w$。树路径最大边用维护路径最大值的倍增 LCA 求。

## Complexity / 复杂度
$O((n+m)\log n)$. $O((n+m)\log n)$。
