# 222 - Polygon Lattice Points

## Problem / 题目
Count the lattice points strictly inside a simple polygon and on its boundary.

统计简单多边形严格内部与边界上的格点数。

## Idea / 思路
By Pick's theorem $A=I+\frac{B}{2}-1$, where $B$ is the number of boundary lattice points and $I$ the interior ones. The boundary count is $B=\sum_{\text{edges}}\gcd(|\Delta x|,|\Delta y|)$, and $2A$ is the integer shoelace value, so $I=\frac{2A-B+2}{2}$.

由皮克定理 $A=I+\frac{B}{2}-1$，其中 $B$ 为边界格点数、$I$ 为内部格点数。边界数 $B=\sum_{\text{边}}\gcd(|\Delta x|,|\Delta y|)$，而 $2A$ 为整数鞋带值，故 $I=\frac{2A-B+2}{2}$。

## Complexity / 复杂度
$O(n\log V)$ for the gcds. gcd 计算 $O(n\log V)$。
