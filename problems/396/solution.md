# 396 - Maximum Building II

## Problem / 题目

For every height $h=1,\dots,n$ and width $w=1,\dots,m$, count placements of an all-empty $h\times w$ rectangle in a forest grid.

对每个高度 $h=1,\dots,n$ 与宽度 $w=1,\dots,m$，统计森林网格中全为空地的 $h\times w$ 矩形摆放数量。

## Idea / 思路

Process each row as the bottom edge of rectangles. Maintain histogram heights
$$H[x]=\text{number of consecutive empty cells ending at the current row in column }x.$$
For any column interval $[l,r]$, the maximum empty rectangle ending at this row and spanning exactly that interval has height
$$\min_{l\le x\le r}H[x].$$
If this minimum is $q$, then the interval contributes one rectangle of width $r-l+1$ for every requested height $1\le h\le q$.

### Assign every interval to one minimum bar / 把每个区间唯一归属给最小柱

For every histogram position $x$, find:

- `L[x]`: first position after the nearest **strictly smaller** height on the left;
- `R[x]`: last position before the nearest **smaller or equal** height on the right.

The asymmetric tie rule (`>=` when popping on the left scan, `>` on the right scan) assigns every interval with repeated minimum heights to exactly one representative bar, avoiding double counting.

Any interval assigned to $x$ chooses a left endpoint among
$$a=x-L[x]+1$$
positions and a right endpoint among
$$b=R[x]-x+1$$
positions. Assume $a\le b$. The number of such intervals of exact width $w$ is the trapezoid sequence
$$1,2,\dots,a-1,a,\dots,a,a-1,\dots,1.$$
It can be added to the width array using a **second difference** with only four updates:

- `+1` at width $1$;
- `-1` at $a+1$;
- `-1` at $b+1$;
- `+1` at $a+b+1$.

Two prefix sums over width reconstruct the trapezoid. Add these updates to row `H[x]` of a table; after processing all bottom rows, the table tells how many intervals have each exact width and **minimum histogram height exactly $q$**.

把每一行依次作为矩形底边，维护柱状图高度
$$H[x]=\text{第 }x\text{ 列以当前行为结尾的连续空格数}。$$
对任意列区间 $[l,r]$，以当前行为底边、横跨该区间的最大空矩形高度为
$$\min_{l\le x\le r}H[x]。$$
若最小值为 $q$，该区间会对每个 $1\le h\le q$ 的请求高度各贡献一个宽度 $r-l+1$ 的矩形。

对每个柱状图位置 $x$，求：

- `L[x]`：左侧最近**严格更小**高度之后的位置；
- `R[x]`：右侧最近**小于等于**当前高度之前的位置。

左右不对称的相等处理（左扫描弹出 `>=`，右扫描弹出 `>`）会把含多个相同最小柱的区间唯一分配给其中一个代表，避免重复计数。

归属于 $x$ 的区间，其左端有
$$a=x-L[x]+1$$
种选择，右端有
$$b=R[x]-x+1$$
种选择。设 $a\le b$，精确宽度 $w$ 的区间数量形成梯形序列
$$1,2,\dots,a-1,a,\dots,a,a-1,\dots,1。$$
该序列可用宽度方向的**二阶差分**只做四次更新：

- 宽度1处 `+1`；
- $a+1$ 处 `-1`；
- $b+1$ 处 `-1`；
- $a+b+1$ 处 `+1`。

沿宽度做两次前缀和即可恢复梯形。把更新写入表格的第 `H[x]` 行；处理所有底边后，表格给出每个精确宽度、且柱状图区间最小高度**恰为 $q$**的数量。

### Convert maximum height to every exact requested height / 从最大高度转换到所有请求高度

An interval with minimum height $q$ supports one rectangle of every height $h\le q$ ending at the current bottom row. Therefore, for each width, take a suffix sum over $q$ from $n$ down to $1$:
$$answer[h][w]=\sum_{q\ge h} exactMinimum[q][w].$$
This yields exactly the number of all-empty $h\times w$ placements.

最小高度为 $q$ 的区间，对每个 $h\le q$ 都支持一个以当前行为底边的高度 $h$ 矩形。因此对每个宽度沿高度从 $n$ 到1做后缀和：
$$answer[h][w]=\sum_{q\ge h}exactMinimum[q][w]。$$
所得即全空 $h\times w$ 矩形数量。

## Complexity / 复杂度

Each grid cell participates in $O(1)$ monotonic-stack and difference operations. Reconstruction and output also touch every size once. Time is $O(nm)$ and memory is $O(nm)$.

每个格子只参与 $O(1)$ 次单调栈与差分操作，恢复和输出也各遍历所有尺寸一次。时间复杂度 $O(nm)$，空间复杂度 $O(nm)$。
