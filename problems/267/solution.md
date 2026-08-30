# 267 - Sliding Window Cost

## Problem / 题目
For each window of $k$ elements, output the minimum total cost to make all of them equal, where changing a value by $d$ costs $d$.

对每个 $k$ 元素窗口，输出把它们全部变相等的最小总代价，把某值改变 $d$ 的代价为 $d$。

## Idea / 思路
The cost is minimized by moving everything to the median, giving $\sum_i |x_i-\text{med}|$. Maintain the two balanced multisets as in the median problem, plus the running sums of each half. Then the cost is $(\text{med}\cdot|\text{lo}|-\text{sumLo})+(\text{sumHi}-\text{med}\cdot|\text{hi}|)$.

代价在把所有值移到中位数时最小，为 $\sum_i |x_i-\text{med}|$。如中位数问题般维护两个平衡多重集合，并维护各半的和。代价即 $(\text{med}\cdot|\text{lo}|-\text{sumLo})+(\text{sumHi}-\text{med}\cdot|\text{hi}|)$。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
