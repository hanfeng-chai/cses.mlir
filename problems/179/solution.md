# 179 - Counting Grids

## Problem / 题目
Count the distinct $n\times n$ grids colored with $2$ colors, where rotations (by $0,90,180,270$ degrees) are considered identical, modulo $10^9+7$. $n$ can be up to $10^9$.

求 $n\times n$、$2$ 种颜色、旋转（$0,90,180,270$ 度）视为相同的不同方格图数，模 $10^9+7$。$n$ 可达 $10^9$。

## Idea / 思路
Burnside over the rotation group $C_4$. The number of cell-orbits is $n^2$ for the identity, $\lceil n^2/4\rceil$ for $90^\circ$ and $270^\circ$, and $\lceil n^2/2\rceil$ for $180^\circ$, so the answer is
$$\frac{2^{n^2}+2\cdot 2^{\lceil n^2/4\rceil}+2^{\lceil n^2/2\rceil}}{4}.$$
The exponents are reduced modulo $p-1$ (Fermat), using $\lceil n^2/4\rceil=(n^2+3)/4$ and $\lceil n^2/2\rceil=(n^2+1)/2$; divide by $4$ with a modular inverse.

在旋转群 $C_4$ 上用 Burnside。格子轨道数：恒等为 $n^2$，$90^\circ$ 与 $270^\circ$ 为 $\lceil n^2/4\rceil$，$180^\circ$ 为 $\lceil n^2/2\rceil$，故答案为
$$\frac{2^{n^2}+2\cdot 2^{\lceil n^2/4\rceil}+2^{\lceil n^2/2\rceil}}{4}.$$
指数按费马小定理对 $p-1$ 取模，其中 $\lceil n^2/4\rceil=(n^2+3)/4$、$\lceil n^2/2\rceil=(n^2+1)/2$；最后乘 $4$ 的模逆元。

## Complexity / 复杂度
$O(\log p)$. $O(\log p)$。
