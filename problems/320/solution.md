# 320 - Forbidden Cities

## Problem / 题目
Answer queries: is there a path from $a$ to $b$ avoiding city $c$?

回答询问：是否存在避开城市 $c$ 的 $a\to b$ 路径？

## Idea / 思路
Build the block-cut tree of the biconnected components. A path avoiding $c$ fails to exist only when $c$ is an articulation point that separates $a$ and $b$, i.e. $c$'s tree node lies on the block-cut-tree path between the representatives of $a$ and $b$ (also NO if $a=c$ or $b=c$). The on-path test uses LCA with binary lifting; a non-articulation $c$ never separates.

建双连通分量的块割树。避开 $c$ 的路径不存在仅当 $c$ 是割点且分隔 $a,b$，即 $c$ 的树结点位于 $a,b$ 代表点的块割树路径上（$a=c$ 或 $b=c$ 时亦为 NO）。在路径判定用倍增 LCA；非割点的 $c$ 永不分隔。

## Complexity / 复杂度
$O((n+m) + q\log n)$. $O((n+m)+q\log n)$。
