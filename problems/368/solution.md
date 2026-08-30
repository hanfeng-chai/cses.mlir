# 368 - Sorting Methods

## Problem / 题目

Given a permutation of $1,\dots,n$, compute the minimum number of operations to sort it under four different move types: (1) swap adjacent elements, (2) swap any two elements, (3) move any element to any position, (4) move any element to the front.

给定 $1,\dots,n$ 的一个排列，分别求在四种操作下把它排好序所需的最少操作次数：(1) 交换相邻元素，(2) 交换任意两个元素，(3) 把任意元素移到任意位置，(4) 把任意元素移到最前面。

## Idea / 思路

Four independent classical results:

1. **Adjacent swaps**: exactly the number of **inversions** — every adjacent swap fixes exactly one inversion, and this is well known to be optimal. Computed with a Fenwick tree, $O(n\log n)$.

2. **Arbitrary swaps**: $n-(\text{number of cycles})$ in the permutation viewed as a function $i\mapsto p_i$. Each cycle of length $\ell$ can be fixed with $\ell-1$ swaps (rotate it into place), and this is optimal, so summing $(\ell-1)$ over all cycles gives $n-(\text{cycle count})$.

3. **Move to any position**: the elements that never need to move must already be in relatively increasing order — i.e. they form an increasing subsequence — and the *largest* such kept subsequence is the standard **LIS**; every other element gets individually reinserted into its correct slot. Answer $=n-\text{LIS}$.

4. **Move to front only**: since moved elements always end up pushed in front of whatever remains, the elements we *never* move must end up as a **suffix** of the final sorted array, and (being untouched) must already appear in strictly increasing *positional* order matching their value order. So find the largest $k$ such that the values $n-k+1,\dots,n$ appear at strictly increasing positions in the original array (checked by simply walking down from value $n$ while $\text{pos}(v)<\text{pos}(v+1)$ continues to hold); answer $=n-k$.

*Sanity check* on $[7,8,2,6,5,1,3,4]$: inversions $=20$; cycle count $=2$ (cycle $1{\to}7{\to}3{\to}2{\to}8{\to}4{\to}6{\to}1$ of length $7$, plus fixed point $5$), giving $8-2=6$; LIS $=3$ (e.g. $1,3,4$), giving $8-3=5$; the value-suffix check finds $k=2$ (values $7,8$ appear at increasing positions $1,2$, but $6$ breaks it since $\text{pos}(6)=4>\text{pos}(7)=1$), giving $8-2=6$ — matching the sample `20 6 5 6` exactly.

四个各自独立的经典结论：

1. **相邻交换**：恰好等于**逆序对**个数——每次相邻交换恰好消除一个逆序对，这是已知的最优策略。用树状数组计算，$O(n\log n)$。

2. **任意交换**：把排列看作函数 $i\mapsto p_i$，答案是 $n-(\text{环的个数})$。长度为 $\ell$ 的环用 $\ell-1$ 次交换即可归位（依次轮转），这是最优的，对所有环求和 $(\ell-1)$ 即得 $n-(\text{环数})$。

3. **移到任意位置**：不需要移动的元素必须已经保持相对递增——即构成一个递增子序列——而能保留的*最长*这样的子序列正是标准的 **LIS**；其余每个元素单独插回自己的正确位置。答案 $=n-\text{LIS}$。

4. **只能移到最前面**：由于被移动的元素总会被推到剩余部分的最前面，那些*永不*移动的元素最终必然构成排好序数组的一段**后缀**，并且（因为没被动过）它们原本就必须按值的顺序出现在严格递增的位置上。所以找最大的 $k$，使值 $n-k+1,\dots,n$ 在原数组中出现在严格递增的位置上（从值 $n$ 往下走，只要 $\text{pos}(v)<\text{pos}(v+1)$ 一直成立就继续）；答案 $=n-k$。

*用 $[7,8,2,6,5,1,3,4]$ 验证：* 逆序对 $=20$；环数 $=2$（一个长度 $7$ 的环 $1{\to}7{\to}3{\to}2{\to}8{\to}4{\to}6{\to}1$，加一个不动点 $5$），得 $8-2=6$；LIS $=3$（如 $1,3,4$），得 $8-3=5$；值后缀检查得 $k=2$（值 $7,8$ 出现在递增的位置 $1,2$，但 $6$ 打破了链，因为 $\text{pos}(6)=4>\text{pos}(7)=1$），得 $8-2=6$——与样例 `20 6 5 6` 完全一致。

## Complexity / 复杂度

$O(n\log n)$ overall (inversions and LIS each need $O(n\log n)$; cycle-counting and the value-suffix check are $O(n)$).

总体 $O(n\log n)$（逆序对和 LIS 各需 $O(n\log n)$；环计数与值后缀检查均为 $O(n)$）。
