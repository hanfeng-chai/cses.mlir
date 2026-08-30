# 268 - Sliding Window Inversions

## Problem / 题目
For each window of $k$ elements, output the number of inversions (pairs with the left element larger).

对每个 $k$ 元素窗口，输出逆序对数（左元素较大的对）。

## Idea / 思路
Maintain a Fenwick tree over the compressed values of the current window and an incremental inversion count. When a new element enters on the right, it forms inversions with every current element greater than it. When the leftmost element leaves, remove the inversions in which it was the larger left element, i.e. the count of current elements smaller than it.

维护当前窗口压缩值上的树状数组与逆序对的增量计数。新元素从右进入时，与当前所有比它大的元素构成逆序对。最左元素离开时，删去其作为较大左元素参与的逆序对，即当前比它小的元素个数。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
