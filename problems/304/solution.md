# 304 - Transfer Speeds Sum

## Problem / 题目
In a tree with edge speeds, $d(a,b)$ is the minimum edge speed on the path $a\to b$. Output $\sum_{a<b} d(a,b)$.

带边速度的树中，$d(a,b)$ 为路径 $a\to b$ 上最小边速。求 $\sum_{a<b} d(a,b)$。

## Idea / 思路
Process edges in **decreasing** speed with a union-find. When an edge of weight $w$ merges components of sizes $s_1$ and $s_2$, every one of the $s_1\cdot s_2$ newly connected pairs has path-minimum exactly $w$ (all previously added edges are $\ge w$), contributing $s_1 s_2 w$.

按速度**降序**用并查集处理边。权 $w$ 的边合并大小 $s_1$、$s_2$ 的分量时，新连通的 $s_1\cdot s_2$ 对的路径最小值恰为 $w$（此前加入的边都 $\ge w$），贡献 $s_1 s_2 w$。

## Complexity / 复杂度
$O(n\alpha(n))$ after sorting. 排序后 $O(n\alpha(n))$。
