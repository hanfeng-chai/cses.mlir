# 326 - All Letter Subgrid Count II

## Problem / 题目

Given an $n\times n$ grid over the first $k$ uppercase letters, count all rectangular subgrids containing every letter at least once. Here $n\le500$.

给定一个由前 $k$ 个大写字母组成的 $n\times n$ 网格，统计至少包含每种字母一次的所有矩形子网格。这里 $n\le500$。

## Idea / 思路

Enumerate the top and bottom rows of the rectangle. For a fixed row band $[t,b]$, compress each column $x$ into a $k$-bit mask
$$M_x=\bigvee_{y=t}^{b} 2^{\text{grid}[y][x]}.$$
Now choosing the left and right columns is exactly choosing a subarray of $M_0,\dots,M_{n-1}$, and the rectangle contains every letter iff the bitwise OR of that subarray equals
$$T=(1\ll k)-1.$$

For each right endpoint `right`, maintain a sliding window starting at `left`. Whenever the window OR is $T$, every rectangle with the same `left` and an ending column $right'\ge right$ is also valid, so this left endpoint contributes `n-right` rectangles. Then remove the leftmost column and repeat while the window still contains all letters. Each possible left endpoint is counted at the first right endpoint where it becomes valid, together with all its right extensions.

The obstacle is that bitwise OR has no inverse: after removing the leftmost mask, `window_or ^ removed` is not correct. Use a queue represented by two stacks:

- the back stack receives new masks and stores prefix ORs;
- the front stack serves removals and also stores prefix ORs;
- the OR of the whole queue is `front_or | back_or`;
- when the front stack is empty, reverse all elements from the back stack into it, recomputing prefix ORs.

Each mask moves from back to front and is removed once, so a complete column scan is amortized $O(n)$ for one fixed row band. Column masks are updated incrementally when `bottom` moves down one row.

枚举矩形的上边界和下边界。固定行带 $[t,b]$ 后，把每一列 $x$ 压缩成一个 $k$ 位掩码
$$M_x=\bigvee_{y=t}^{b}2^{\text{grid}[y][x]}。$$
此时选择左右边界等价于选择 $M_0,\dots,M_{n-1}$ 的一个子数组；当且仅当该子数组的按位或等于
$$T=(1\ll k)-1$$
时，矩形包含全部字母。

对每个右端点 `right`，维护从 `left` 开始的滑动窗口。若窗口 OR 已为 $T$，则保持同一个 `left`、把右边界扩展到任意 $right'\ge right$ 都仍然合法，所以该左端点一次贡献 `n-right` 个矩形。随后删除最左列，只要窗口仍合法就继续。这样每个左端点都在第一次变得合法的右端点处计数，并同时计入所有向右扩展。

难点是按位 OR 没有逆运算：删除最左掩码后，不能用 `window_or ^ removed` 更新。使用两个栈实现队列：

- 后栈接收新掩码，并保存前缀 OR；
- 前栈负责删除，也保存前缀 OR；
- 整个队列的 OR 是 `front_or | back_or`；
- 当前栈为空时，把后栈元素逆序全部搬过去，并重新计算前缀 OR。

每个掩码只会进入后栈、搬到前栈、再被删除各一次，因此固定行带的一次列扫描摊还为 $O(n)$。下边界每向下一行，逐列增量更新列掩码即可。

## Complexity / 复杂度

There are $O(n^2)$ row bands and each uses an $O(n)$ column update/scan, so time is $O(n^3)$. Memory is $O(n^2)$ for per-cell masks and $O(n)$ working space.

共有 $O(n^2)$ 个行带，每个行带用 $O(n)$ 更新并扫描列，因此时间复杂度 $O(n^3)$。每格掩码占 $O(n^2)$ 空间，工作区占 $O(n)$。
