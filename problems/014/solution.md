# 014 - Tower of Hanoi

## Problem / 题目

Move a stack of $n$ disks from peg $1$ to peg $3$, one disk per move, never placing a larger disk on a smaller one. Print the minimum number of moves and the moves themselves.

把 $n$ 个盘子从柱 $1$ 移到柱 $3$，每次移动一个盘子，且永远不能把大盘压在小盘上。输出最少移动次数以及每一步的移动。

## Idea / 思路

Use the classic recursion: to move $n$ disks from `from` to `to` using `via` as spare, first move the top $n-1$ disks from `from` to `via`, then move the largest disk from `from` to `to`, then move the $n-1$ disks from `via` to `to`. This is provably optimal and uses exactly $2^n - 1$ moves, which we print first.

使用经典递归：要把 $n$ 个盘从 `from` 借助 `via` 移到 `to`，先把上面 $n-1$ 个盘从 `from` 移到 `via`，再把最大的盘从 `from` 移到 `to`，最后把 $n-1$ 个盘从 `via` 移到 `to`。可证明这是最优的，恰好需要 $2^n - 1$ 步，我们先把它输出。

## Complexity / 复杂度

The number of moves is $2^n - 1$, and the recursion produces each move in constant time, so the total time is $O(2^n)$.

移动次数为 $2^n - 1$，递归以常数时间产生每一步，因此总时间为 $O(2^n)$。
