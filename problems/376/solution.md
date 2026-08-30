# 376 - Increasing Array II

## Problem / 题目

Using unit increments/decrements on individual elements, make the array non-decreasing with the minimum total number of moves.

用单位加一/减一操作修改元素，使数组变为非降的，求最少总操作次数。

## Idea / 思路

This is the classic **L1 isotonic regression** problem, solved online with a max-heap. Process elements left to right, maintaining a max-heap of the "effective values" seen so far (conceptually, values that have already been pooled together into one non-decreasing run get represented by their *shared* value). For each new element $x_i$: push it onto the heap. If the heap's current maximum exceeds $x_i$, that maximum has to come down to $x_i$ to keep things non-decreasing — add the difference to the answer, then **replace** that maximum in the heap with $x_i$ (pop the max, push $x_i$).

Why this is optimal: whenever a new element is smaller than everything pooled before it, some previous value(s) must be lowered to meet it (raising $x_i$ instead would cost the same or more and can only get worse for future comparisons); replacing the *maximum* pooled value specifically with $x_i$ is the correct greedy choice, and this is the standard heap-based algorithm for weighted L1 isotonic regression.

*Sanity check:* $x=[3,8,5,6,5]$: heap-max exceeds the current element at $i=3$ ($8>5$, cost $+3$) and $i=5$ ($6>5$, cost $+1$), total $4$ — matching the sample.

这是经典的**L1 等距回归（isotonic regression）**问题，用最大堆在线求解。从左到右处理元素，用一个最大堆维护目前"有效值"的多重集（概念上，已经被合并进同一个非降"段"的值，会被它们*共享*的那个值代表）。对每个新元素 $x_i$：先压入堆。如果堆顶（最大值）超过了 $x_i$，那么这个最大值必须降到 $x_i$ 才能保持非降——把差值累加进答案，然后把堆里的那个最大值**替换**成 $x_i$（弹出最大值，压入 $x_i$）。

为什么这是最优的：一旦新元素比之前合并的所有值都小，就必须把之前的某些值降下来匹配它（反过来把 $x_i$ 提高，代价不会更小，而且对后面的比较只会更不利）；把被合并的*最大*那个值恰好换成 $x_i$，正是正确的贪心选择，这也是加权 L1 等距回归的标准堆算法。

*验证：* $x=[3,8,5,6,5]$：在 $i=3$ 处堆顶超过当前元素（$8>5$，代价 $+3$），在 $i=5$ 处也超过（$6>5$，代价 $+1$），总计 $4$——与样例一致。

## Complexity / 复杂度

$O(n\log n)$ time (one heap push and possibly one pop+push per element), $O(n)$ memory.

时间 $O(n\log n)$（每个元素一次入堆，可能再一次出堆+入堆），空间 $O(n)$。
