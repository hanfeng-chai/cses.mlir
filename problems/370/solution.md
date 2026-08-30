# 370 - List of Sums

## Problem / 题目

Given list $B$, the multiset of all $\binom n2$ pairwise sums of an unknown list $A$ of $n$ positive integers, reconstruct $A$ (any valid answer is accepted).

给定列表 $B$（一个未知的、含 $n$ 个正整数的列表 $A$ 的全部 $\binom n2$ 个两两之和构成的多重集），还原 $A$（任意合法答案均可）。

## Idea / 思路

Sort $A$ (conceptually) as $a_1\le a_2\le\dots\le a_n$. The two smallest pairwise sums overall are always $a_1{+}a_2$ (the very smallest) and $a_1{+}a_3$ (the second smallest — it beats every sum not involving $a_1$ or $a_2$). So if $a_1$ were known, the rest can be reconstructed **greedily**: keep a multiset of remaining sums; repeatedly take its current smallest value $s$ — this is always $a_1$ plus the next not-yet-found element (any "cross sum" between two already-found elements $\ge a_2$ must be removed *immediately* once both its parts are known, so it never gets mistaken for a "new" element) — set the new element to $s-a_1$, then remove, for every previously found element $a_j$ ($j\ge2$), the sum $a_j+(s-a_1)$ from the multiset (it's now accounted for).

The one missing piece is $a_1$ itself. From $a_1+a_2=B_0$ and $a_1+a_3=B_1$, we'd get $a_1$ directly if we knew $a_2+a_3$ — and $a_2+a_3$ **is** guaranteed to be one of the values in $B$ (empirically, always among the smallest handful, though not at one fixed rank — see the discussion below). So: try each of the first $\min(m,300)$ smallest values of $B$ as a candidate for $a_2+a_3$, derive $a_1=\tfrac{B_0+B_1-\text{candidate}}{2}$, and attempt the full greedy reconstruction; keep the first candidate for which it fully succeeds (uses up the whole multiset with no contradiction). Trying a generous but bounded prefix of candidates (rather than assuming a fixed rank like "$B_2$") was chosen after confirming by construction that $a_1+a_4$ can beat $a_2+a_3$ into third place for some inputs, so the rank of $a_2+a_3$ isn't fixed — this bounded-search approach was verified against thousands of randomly generated cases (including many with duplicate values) before being trusted.

Since many different arrays can share the same pairwise-sum multiset, this problem is graded with a checker that recomputes all pairwise sums of the printed array and compares the resulting multiset to $B$, rather than requiring one fixed array.

把 $A$（概念上）排序为 $a_1\le a_2\le\dots\le a_n$。全局最小的两个两两之和永远是 $a_1{+}a_2$（最小的）和 $a_1{+}a_3$（第二小的——它比任何不含 $a_1$ 或 $a_2$ 的和都小）。所以只要知道 $a_1$，剩下的就能**贪心**还原：维护一个"剩余和"的多重集；反复取出其中当前最小的值 $s$——它必然是 $a_1$ 加上下一个尚未找到的元素（任意两个*已找到*且都 $\ge a_2$ 的元素之间的"交叉和"，一旦两部分都已知就要*立刻*从多重集中删除，这样它才不会被误认成"新"元素）——令新元素为 $s-a_1$，然后对每个之前已找到的元素 $a_j$（$j\ge2$），把 $a_j+(s-a_1)$ 从多重集中删除（它现在已经"记过账"了）。

唯一缺的一环是 $a_1$ 本身。由 $a_1+a_2=B_0$ 和 $a_1+a_3=B_1$，只要知道 $a_2+a_3$ 就能直接解出 $a_1$——而 $a_2+a_3$ **保证**是 $B$ 中的某个值（经验上，它总在最小的那一小撮里，但并非固定排名——见下文）。做法是：把 $B$ 中最小的 $\min(m,300)$ 个值都当作 $a_2+a_3$ 的候选，逐一算出 $a_1=\tfrac{B_0+B_1-\text{候选}}{2}$，并尝试完整的贪心还原；取第一个能完全成功（用完整个多重集且无矛盾）的候选。之所以选择"宽松但有界的候选范围"而不是假定固定排名（比如"就是 $B_2$"），是因为构造发现某些输入下 $a_1+a_4$ 可能挤到第三小的位置，使 $a_2+a_3$ 的排名不固定——这种有界搜索的做法，在提交前已经用数千个随机生成的用例（包括大量含重复值的情形）做了验证。

由于满足同一个两两和多重集的数组可能不止一个，本题用 checker 评测：重新计算输出数组的全部两两之和，与 $B$ 的多重集比较，而不要求输出某个固定的数组。

## Complexity / 复杂度

Each of the $O(\min(m,300))$ candidates for $a_1$ triggers a full $O(n^2\log m)$ greedy reconstruction attempt (using a multiset), so overall about $O(\min(m,300)\cdot n^2\log m)$; with $n\le100$ this is comfortably fast.

每个候选 $a_1$（共 $O(\min(m,300))$ 个）都要触发一次完整的 $O(n^2\log m)$ 贪心还原尝试（用多重集），总体约 $O(\min(m,300)\cdot n^2\log m)$；$n\le100$ 时运行很快。
