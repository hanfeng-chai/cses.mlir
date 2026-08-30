# 375 - K Subset Sums II

## Problem / 题目

Given $n$ integers, consider all subsets containing exactly $m$ elements. Output the $k$ smallest subset sums in nondecreasing order, including equal sums with their correct multiplicities.

给定 $n$ 个整数，考虑所有恰好包含 $m$ 个元素的子集。按非递减顺序输出最小的 $k$ 个子集和；相等的和必须按不同下标子集保留正确重数。

## Idea / 思路

Sort the values as $a_0\le a_1\le\dots\le a_{n-1}$. Represent an $m$-subset by increasing selected indices
$$0\le i_0<i_1<\dots<i_{m-1}<n.$$
The minimum subset is $(0,1,\dots,m-1)$ with sum $S_0$.

We need a rooted tree that contains every other index combination exactly once and whose edge weights are nonnegative. Then best-first traversal with a min-heap outputs subset sums globally in sorted order.

### Combination tree / 组合树

The root has one child obtained by moving the last selected index from $m-1$ to $m$. A non-root tree state stores:

- `hole`: an unselected index immediately to the left of a movable selected block;
- `moving`: the currently movable selected index;
- `limit`: the next selected index to the right, or $n$ if none;
- the current subset sum.

It has up to two children:

1. **Move the current selected index right:** if `moving+1 < limit`, replace `moving` by `moving+1`. The sum changes by
   $$-a_{moving}+a_{moving+1}.$$
2. **Open a hole one position further left:** if `hole>0`, replace selected index `hole-1` by the current hole `hole`. The old hole becomes selected, and `hole-1` becomes the new hole; the new movable index is `hole`, and its limit is the old `moving`. The sum changes by
   $$-a_{hole-1}+a_{hole}.$$

This is not merely a single replacement chain. The second transition recursively creates a new movable level to the left, while retaining the already selected indices to its right through `limit`. It is the hierarchical structure needed for combinations such as deviations in several separated positions.

Every increasing $m$-index combination except the root has a unique parent: look at the leftmost active gap in its canonical right-to-left increment history. Either its active index can be shifted one step left (inverse of transition 1), or filling that gap closes the current level and returns to the previous one (inverse of transition 2). Thus no combination is omitted or generated twice.

Because $a$ is sorted, both edge increments are nonnegative. Consequently each child sum is at least its parent sum, so a min-heap best-first traversal of this tree emits all subset sums in nondecreasing order. Equal values and equal sums are safe: nodes represent distinct index combinations, hence multiplicities are preserved.

将数值排序为 $a_0\le a_1\le\dots\le a_{n-1}$。一个大小为 $m$ 的子集用严格递增下标表示：
$$0\le i_0<i_1<\dots<i_{m-1}<n。$$
最小子集是 $(0,1,\dots,m-1)$，其和记为 $S_0$。

需要构造一棵根树，使每个其他下标组合恰好出现一次，并且每条边的权值非负。这样用小顶堆做最佳优先遍历，就会按全局非递减顺序输出子集和。

根节点唯一的孩子把最后一个选中下标从 $m-1$ 移到 $m$。每个非根状态保存：

- `hole`：可移动选中块左侧紧邻的未选下标；
- `moving`：当前可向右移动的选中下标；
- `limit`：右侧下一个已选下标；若不存在则为 $n$；
- 当前子集和。

它最多有两个孩子：

1. **把当前选中下标右移：** 若 `moving+1 < limit`，用 `moving+1` 替换 `moving`，和变化
   $$-a_{moving}+a_{moving+1}。$$
2. **把空位向左再开一层：** 若 `hole>0`，用当前空位 `hole` 替换已选下标 `hole-1`。旧空位被填上，`hole-1` 成为新空位；新的可移动下标为 `hole`，上界为旧 `moving`。和变化
   $$-a_{hole-1}+a_{hole}。$$

这并非简单的单一替换链。第二种转移会在更左侧递归创建新的可移动层，并通过 `limit` 保留右侧已经选定的下标；这正是表示多个分离位置同时偏移所需的层次结构。

除根外，每个递增下标组合都有唯一父节点：观察其规范化“从右到左增加下标”历史中的最左活动空位。要么活动下标可左移一步（转移1的逆），要么填回该空位会关闭当前层、返回上一层（转移2的逆）。因此没有组合遗漏，也没有组合重复生成。

由于 $a$ 已排序，两种边增量都非负，所以孩子的和不小于父亲。对这棵树使用小顶堆最佳优先遍历，就会按非递减顺序输出全部子集和。即使数值重复、和相等也没有问题：节点对应不同下标组合，因此重数被正确保留。

## Complexity / 复杂度

Sorting costs $O(n\log n)$. At most two states are inserted for each of the $k$ outputs, so heap work is $O(k\log k)$. Memory is $O(n+k)$.

排序需要 $O(n\log n)$。每输出一个结果至多插入两个状态，因此堆操作总计 $O(k\log k)$。空间复杂度 $O(n+k)$。
