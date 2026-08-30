# 052 - Nearest Smaller Values

## Problem / 题目

For each position, find the nearest position to its left holding a strictly smaller value (or $0$ if none).

对每个位置，找出其左侧最近的、值严格更小的位置（若不存在则为 $0$）。

## Idea / 思路

Maintain a stack of indices whose values are strictly increasing from bottom to top. For each new element, pop while the value at the stack top is $\ge$ the current value; whatever remains on top (if anything) is the nearest smaller element to the left. Then push the current index. Each index is pushed and popped once.

维护一个栈，其中下标对应的值自底向上严格递增。对每个新元素，当栈顶的值 $\ge$ 当前值时不断弹出；弹完后栈顶（若有）就是左侧最近的更小元素。然后把当前下标压栈。每个下标只入栈、出栈各一次。

## Complexity / 复杂度

Each element is pushed and popped at most once, so the time is $O(n)$.

每个元素至多入栈、出栈各一次，因此时间为 $O(n)$。
