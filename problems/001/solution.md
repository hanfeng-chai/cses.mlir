# 001 - Weird Algorithm

## Problem / 题目

We start from an integer $n$ and repeatedly apply the Collatz rule: if the current value is even, divide it by two; if it is odd, multiply it by three and add one. We print every value we visit, until we finally reach $1$.

我们从整数 $n$ 出发，反复套用 Collatz 规则：当前值若为偶数就除以二，若为奇数就乘三再加一。沿途打印经过的每一个值，直到最终到达 $1$。

## Idea / 思路

This is a pure simulation — just follow the rule step by step. The only real trap is the magnitude of the numbers: although $n \le 10^6$, the intermediate values can grow far beyond the 32-bit integer range. Using a 32-bit `int` would overflow and give wrong answers, so we keep the value in a 64-bit `long long`.

这是一道纯模拟题——照着规则一步步走即可。唯一的真正陷阱是数值的大小：虽然 $n \le 10^6$，但中间结果可能远远超出 32 位整数范围。用 32 位的 `int` 会溢出从而出错，所以我们把值存在 64 位的 `long long` 里。

## Complexity / 复杂度

Each step is $O(1)$, and the number of steps (the length of the Collatz path) is small in practice, so the whole program runs comfortably within the limits.

每一步都是 $O(1)$，而步数（Collatz 路径长度）在实践中很小，因此整个程序能轻松地在限制内完成。
