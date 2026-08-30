# 125 - Forest Queries

## Problem / 题目

Given an $n \times n$ grid of trees and empty cells, answer $q$ queries each asking how many trees lie inside a rectangle.

给定一个 $n \times n$ 的树与空格网格，回答 $q$ 个询问，每个问某矩形内有多少棵树。

## Idea / 思路

Build a 2D prefix-sum table $p[i][j]$ = number of trees in the rectangle from $(1,1)$ to $(i,j)$, using $p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + \text{tree}(i,j)$. A rectangle query is then answered by inclusion–exclusion of four prefix values in $O(1)$.

构建二维前缀和 $p[i][j]$ = 从 $(1,1)$ 到 $(i,j)$ 矩形内的树数，递推 $p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + \text{tree}(i,j)$。矩形询问用四个前缀值的容斥在 $O(1)$ 作答。

## Complexity / 复杂度

Building is $O(n^2)$ and each query is $O(1)$.

构建 $O(n^2)$，每个询问 $O(1)$。
