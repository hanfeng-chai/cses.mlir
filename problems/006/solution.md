# 006 - Number Spiral

## Problem / 题目

An infinite grid is filled in a spiral pattern starting with $1$ in the upper-left corner. For each query $(y, x)$ we must output the number written in row $y$, column $x$. There can be up to $10^5$ queries with coordinates up to $10^9$, so we need an $O(1)$ formula per query.

一个无限网格以螺旋方式填充，左上角是 $1$。对每个查询 $(y, x)$，我们要输出第 $y$ 行、第 $x$ 列上的数字。查询最多有 $10^5$ 个，坐标可达 $10^9$，所以每次查询需要一个 $O(1)$ 的公式。

## Idea / 思路

Think of the grid as nested L-shaped "layers". The cell $(y, x)$ belongs to layer $m = \max(y, x)$, and the largest number in that layer is $m^2$. Let $\text{base} = (m-1)^2$ be the largest number of the previous layer. The numbers in layer $m$ run along its bottom row and right column; the direction depends on the parity of $m$:

把网格看成一圈圈嵌套的 L 形"层"。格子 $(y, x)$ 属于第 $m = \max(y, x)$ 层，该层中最大的数是 $m^2$。令 $\text{base} = (m-1)^2$ 为上一层的最大数。第 $m$ 层的数字沿着它的底行和右列分布，方向取决于 $m$ 的奇偶：

- If $m$ is even, the count goes down the right column then left along the bottom row: value is $\text{base}+y$ when $x=m$, otherwise $\text{base}+(2m-x)$.
- If $m$ is odd, the direction is mirrored: value is $\text{base}+x$ when $y=m$, otherwise $\text{base}+(2m-y)$.

- 若 $m$ 为偶数，数字沿右列向下、再沿底行向左：当 $x=m$ 时值为 $\text{base}+y$，否则为 $\text{base}+(2m-x)$。
- 若 $m$ 为奇数，方向镜像：当 $y=m$ 时值为 $\text{base}+x$，否则为 $\text{base}+(2m-y)$。

## Watch out / 注意

With coordinates up to $10^9$, $\text{base}=(m-1)^2$ can reach about $10^{18}$, so all arithmetic must use `long long`.

坐标可达 $10^9$ 时，$\text{base}=(m-1)^2$ 可达约 $10^{18}$，因此所有运算都要用 `long long`。

## Complexity / 复杂度

$O(1)$ per query, $O(t)$ overall.

每次查询 $O(1)$，总体 $O(t)$。
