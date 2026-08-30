# 262 - Sliding Window Or

## Problem / 题目
For a generated array of up to $10^7$ values, output the XOR of the bitwise ORs of all windows of $k$ elements.

对生成的至多 $10^7$ 个值的数组，输出所有 $k$ 元素窗口按位或的异或。

## Idea / 思路
OR is not invertible, so use the "queue from two stacks" trick: each stack stores running ORs, so the OR of the whole queue is the combination of the two stack tops. Pushing is $O(1)$; popping moves elements between stacks, amortized $O(1)$. This yields the OR of each window in linear total time.

按位或不可逆，故用「两个栈模拟队列」技巧：每个栈维护前缀或，整队的或即两栈顶的合并。入队 $O(1)$；出队时在两栈间搬移元素，均摊 $O(1)$。由此线性总时间得到每个窗口的或。

## Complexity / 复杂度
$O(n)$. $O(n)$。
