# 325 - All Letter Subgrid Count I

## Problem / 题目

Given an $n\times n$ grid over the first $k$ uppercase letters, count the square subgrids that contain every one of the $k$ letters at least once. Here $n\le3000$, so enumerating every side length for every top-left corner is too slow.

给定一个由前 $k$ 个大写字母组成的 $n\times n$ 网格，统计至少包含每种字母一次的正方形子网格数量。这里 $n\le3000$，不能对每个左上角再枚举全部边长。

## Idea / 思路

For a fixed top-left corner $(y,x)$ and letter $c$, define
$$D[y][x][c]=\text{the minimum side length of a square starting at $(y,x)$ that contains $c$}.$$
If no such square fits, $D$ is larger than the grid.

Where can the first useful occurrence of $c$ lie? Relative to $(y,x)$, every cell belongs to exactly one of three regions:

1. the top row $(y,x'),\ x'\ge x$;
2. the left column $(y',x),\ y'\ge y$;
3. the strict interior whose top-left corner is $(y+1,x+1)$.

Maintain `nearest_right[c]`, the closest occurrence of $c$ on the current row at or right of $x$, and `nearest_below[x][c]`, the closest occurrence of $c$ in column $x$ at or below $y$. Then the three possible side lengths are
$$R_c-x+1,\qquad B_c-y+1,\qquad D[y+1][x+1][c]+1.$$
Therefore
$$D[y][x][c]=\min\big(R_c-x+1,\ B_c-y+1,\ D[y+1][x+1][c]+1\big).$$

Process rows bottom-to-top and columns right-to-left, so all three values are already known. For a square to contain **all** letters, its side must be at least
$$L(y,x)=\max_{0\le c<k}D[y][x][c].$$
The largest square fitting at this corner has side
$$M(y,x)=\min(n-y,n-x).$$
Thus this corner contributes
$$\max(0,M-L+1)$$
valid squares, because once all letters are present, enlarging the square cannot remove any letter.

Only the next DP row is needed, so `D` is stored for two row parities. The nearest occurrence table uses $O(nk)$ memory. One implementation detail matters at the maximum constraint: a C-style row buffer read by `cin >> row` needs $n+1$ bytes, because the terminating `\0` is also written; using exactly $n$ bytes causes a one-byte overflow on every row.

对固定左上角 $(y,x)$ 和字母 $c$，定义
$$D[y][x][c]=\text{以 $(y,x)$ 为左上角、且包含 $c$ 的正方形的最小边长}。$$
若不存在，则令其大于网格尺寸。

字母 $c$ 的第一个有效出现位置相对 $(y,x)$ 必然属于三个互不重叠的区域之一：

1. 顶行 $(y,x')$，其中 $x'\ge x$；
2. 左列 $(y',x)$，其中 $y'\ge y$；
3. 左上角为 $(y+1,x+1)$ 的严格内部区域。

维护当前行中 $x$ 右侧最近的 $c$ 位置 `nearest_right[c]`，以及第 $x$ 列中 $y$ 下方最近的 $c$ 位置 `nearest_below[x][c]`。三种候选边长分别是
$$R_c-x+1,\qquad B_c-y+1,\qquad D[y+1][x+1][c]+1，$$
所以
$$D[y][x][c]=\min\big(R_c-x+1,\ B_c-y+1,\ D[y+1][x+1][c]+1\big)。$$

按行从下到上、按列从右到左处理，递推所需的三个量都已知。要包含**所有**字母，边长至少为
$$L(y,x)=\max_{0\le c<k}D[y][x][c]。$$
该左上角能放下的最大边长为
$$M(y,x)=\min(n-y,n-x)。$$
因此贡献
$$\max(0,M-L+1)$$
个正方形；因为一旦已经包含全部字母，继续扩大不会让任何字母消失。

DP 只依赖下一行，因此只保留奇偶两行。最近出现位置表占 $O(nk)$ 空间。最大规模下还有一个重要实现细节：用 `cin >> row` 读入 C 风格字符数组时，需要额外一个字节存放结尾的 `\0`；若第二维恰好只有 $n$，每行都会越界一字节。

## Complexity / 复杂度

There are $n^2$ corners and $k\le26$ letters per corner, so time is $O(n^2k)$. Extra DP/nearest-occurrence memory is $O(nk)$, plus $O(n^2)$ for the input grid.

共有 $n^2$ 个左上角，每个处理 $k\le26$ 个字母，时间复杂度 $O(n^2k)$。DP 与最近位置的额外空间为 $O(nk)$，输入网格占 $O(n^2)$。
