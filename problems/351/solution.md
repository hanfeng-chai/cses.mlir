# 351 - Advertisement

## Problem / 题目

A fence consists of $n$ boards of width $1$ and given heights. Find the maximum-area axis-aligned rectangle that fits under the "skyline" formed by the boards.

一排 $n$ 块宽度为 $1$、高度各异的木板组成一道围栏。求能嵌在这个"天际线"轮廓下方的最大矩形面积。

## Idea / 思路

This is the classic **largest rectangle in a histogram** problem. For every board $i$, consider the biggest rectangle whose height equals $h_i$: its width extends left and right as far as neighboring bars stay $\ge h_i$. Computing this "how far can I extend" naively is $O(n)$ per bar; instead, use a **monotonic increasing stack** of bar indices.

Scan bars left to right (with a virtual bar of height $0$ appended at the end to flush everything out). Keep the stack's heights increasing. When the current bar's height is *less* than the height at the top of the stack, that top bar can never extend any further right (its rectangle is now fully determined): pop it, and its width is the gap between the current position and the (new) element now below it on the stack (or the very start, if the stack becomes empty) — because that's exactly the range over which it was the *minimum* height seen. Update the best answer with `height × width`, then repeat the popping with the new stack top if it's also taller than the current bar. Finally push the current bar's index.

Every bar is pushed once and popped once, so the whole scan is $O(n)$, and every bar's maximal rectangle (with that bar's height as the limiting height) is considered exactly once — including the global optimum.

这是经典的**直方图中最大矩形**问题。对每块木板 $i$，考虑高度恰好为 $h_i$ 的最大矩形：它的宽度会向左右延伸，直到邻近的木板低于 $h_i$ 为止。如果对每块木板都暴力地去找这个延伸范围是 $O(n)$，效率太低；改用一个**高度单调递增的栈**存木板下标。

从左到右扫描木板（末尾补一个高度为 $0$ 的虚拟木板，把栈里剩下的都"冲"出来）。保持栈中高度递增。当当前木板的高度*小于*栈顶的高度时，说明栈顶那块木板不可能再往右扩展了（它的矩形范围已经确定）：把它弹出，它的宽度就是当前位置与"弹出后新的栈顶"（或栈空则算到最开始）之间的间隔——因为这恰好是它作为"目前为止的最小高度"所覆盖的范围。用 `高度 × 宽度` 更新答案，然后继续用新的栈顶跟当前木板比较，可能还要继续弹出。最后把当前木板下标压入栈。

每块木板恰好入栈一次、出栈一次，整个扫描是 $O(n)$，并且每块木板（以它的高度为限制高度）对应的最大矩形恰好被考虑一次——其中就包含全局最优解。

## Complexity / 复杂度

$O(n)$ time and memory (one monotonic stack pass).

时间、空间均为 $O(n)$（一次单调栈扫描）。
