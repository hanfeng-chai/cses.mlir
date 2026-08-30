# 294 - Grid Path Construction

## Problem / 题目

Given an $n\times m$ rectangular grid and two distinct cells $a$ and $b$, construct a path that starts at $a$, ends at $b$, and visits every grid cell exactly once, or report that no such path exists.

给定一个 $n\times m$ 矩形网格以及两个不同格子 $a,b$，构造一条从 $a$ 出发、在 $b$ 结束、且恰好访问每个格子一次的路径；若不存在则输出无解。

## Idea / 思路

This asks for a Hamiltonian path in a rectangular grid graph with prescribed endpoints. The main difficulty is not only constructing the path, but also recognizing the few thin-grid exceptions where the usual checkerboard parity condition is not sufficient.

这是在矩形网格图中构造一条端点指定的 Hamilton 路径。难点不仅是构造，还包括识别少数“很薄的网格”例外：这些情况下，普通的棋盘黑白奇偶条件并不充分。

### 1. Exact feasibility test / 精确可行性判定

Color cell $(y,x)$ by $(y+x)\bmod 2$. Every move changes color, so:

- If $nm$ is even, the two endpoints must have different colors.
- If $nm$ is odd, both endpoints must be on the majority color (color $0$ when $(1,1)$ is treated as color $0$).

For grids whose smaller dimension is at least $4$, these parity conditions are also sufficient. Thin grids require extra cases:

- $1\times m$: the only Hamiltonian path is the straight line, so the endpoints must be the two ends.
- $2\times m$: endpoints in the same column work only at the first or last column; otherwise endpoints in different columns work exactly when their colors differ.
- $3\times m$ with even area: besides opposite colors, there are two directional obstructions involving a minority-color endpoint. After rotating/mirroring so the left endpoint is first, a minority endpoint cannot leave too many columns trapped behind it; the implementation encodes these two symmetric inequalities directly.

This exact test was independently checked against bitmask Hamilton-path DP for every rectangle with at most $16$ cells: $26$ board sizes and $2756$ ordered endpoint pairs, with zero mismatches.

按 $(y+x)\bmod2$ 给格子染黑白色。每走一步颜色都会改变，因此：

- 若 $nm$ 为偶数，两个端点必须异色；
- 若 $nm$ 为奇数，两个端点都必须位于数量较多的颜色上（把 $(1,1)$ 视为颜色 $0$ 时，即颜色 $0$）。

当网格较短的一边至少为 $4$ 时，这些奇偶条件也是充分条件。薄网格需要额外处理：

- $1\times m$：Hamilton 路径只能是一条直线，端点必须是两端；
- $2\times m$：若端点同列，则该列只能是第一列或最后一列；若端点不同列，则恰好在端点异色时可行；
- 面积为偶数的 $3\times m$：除异色外，还存在两个关于少数色端点的方向性障碍。旋转、镜像并把左端点归一化后，少数色端点不能把过多列封死在身后；代码直接实现了这两个对称不等式。

该判定已经用独立的位压缩 Hamilton 路径 DP 穷举验证：所有不超过 $16$ 格的矩形，共 $26$ 种尺寸、$2756$ 组有序端点，零不一致。

### 2. Normalize by symmetry / 用对称变换归一化

The constructor first uses grid symmetries so that $n\le m$, $s_x\le t_x$, and $s_y\le t_y$:

- rotate the grid when $n>m$;
- mirror left-right when the start is to the right of the target;
- mirror up-down when the start is below the target.

The recursive answer is transformed back by replacing each direction character accordingly. This reduces many geometric cases to one canonical orientation.

构造器先利用网格对称性归一化到 $n\le m$、$s_x\le t_x$、$s_y\le t_y$：

- 当 $n>m$ 时旋转网格；
- 起点在终点右侧时左右镜像；
- 起点在终点下方时上下镜像。

递归返回后再相应替换方向字符，把路径映射回原网格。这样大量几何情况都被归并到同一个标准方向。

### 3. Recursive decomposition / 递归分块

After normalization, the rectangle is reduced using the following operations:

1. **Small exact base.** Rectangles up to $4\times5$ are solved by DFS. The DFS orders candidates by onward degree (Warnsdorff-style heuristic) and prunes whenever the unvisited cells become disconnected.
2. **Peel two columns.** If both endpoints remain in the rectangle after removing the leftmost or rightmost two columns, recursively solve the smaller rectangle. Any vertical edge on its boundary can be replaced by a Hamiltonian path through the removed $n\times2$ strip, then reconnected to the original edge. Thus two complete columns are inserted without changing the global endpoints.
3. **Horizontal split.** Try a cut between rows $i$ and $i+1$. If the upper and lower rectangles are both feasible with endpoints chosen on the same crossing column, recursively solve both and join them with one `D` move.
4. **Vertical split.** Symmetrically, split between two columns and join the recursively constructed paths with one `R` move.

Every recursive call strictly decreases the rectangle area. The feasibility test guarantees that only valid subproblems are selected. The special adjacent-endpoint pattern in a $2\times m$ strip is constructed directly by walking to one end, traversing the other row, and returning to the target.

归一化后，使用以下操作递归缩小矩形：

1. **小矩形精确求解。** 不超过 $4\times5$ 的矩形用 DFS 求解。DFS 按后续可走度数排序候选点（类似 Warnsdorff 规则），并在未访问格子不再连通时立即剪枝。
2. **剥离两列。** 若删除最左或最右两列后两个端点仍在剩余矩形中，则先递归求解较小矩形。其边界上的任意一条竖边，都可以替换成一条遍历被删除的 $n\times2$ 条带的 Hamilton 路径，再接回原边。因此可以插入完整两列而不改变全局端点。
3. **水平切分。** 枚举第 $i$、$i+1$ 行之间的切口。若上下两个矩形分别在同一跨越列上选择端点后都可行，就递归构造两部分并用一个 `D` 连接。
4. **竖直切分。** 对称地在两列之间切开，递归构造后用一个 `R` 连接。

每个递归调用都会严格减小矩形面积；可行性判定保证只选择合法子问题。$2\times m$ 条带中两个端点同一行且相邻的特殊形状，直接通过“先走到一端、遍历另一行、再回到终点”构造。

### 4. Validation / 验证

Because the answer is non-unique, `checker.cpp` compares only the YES/NO verdict with the jury, then simulates every reported move and verifies that the path stays inside the grid, never revisits a cell, has length $nm-1$, and ends at the requested target. In addition to all local tests, maximum-size random cases were structurally validated before submission.

由于答案不唯一，`checker.cpp` 只把 YES/NO 与裁判结果比较，然后模拟输出路径的每一步，检查它始终在网格内、不重复访问、长度为 $nm-1$，并最终到达指定终点。提交前还额外验证了最大规模随机用例的路径结构。

## Complexity / 复杂度

Outside the constant-size DFS bases, each recursive level scans at most $O(nm)$ candidate cuts/edges and reduces the rectangle. With $n,m\le50$, the conservative bound is polynomial and easily fits the limit; the produced path itself has length $nm-1$, so $\Omega(nm)$ output time is unavoidable. Memory usage is $O(nm)$.

除常数大小的 DFS 基础情形外，每层递归至多扫描 $O(nm)$ 个切口或边，并严格缩小矩形。在 $n,m\le50$ 下，即使采用保守的多项式上界也远在时限内；输出路径本身就有 $nm-1$ 个字符，因此 $\Omega(nm)$ 输出时间不可避免。空间复杂度为 $O(nm)$。
