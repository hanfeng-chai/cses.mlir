# 386 - Replace with Difference

## Problem / 题目

Repeatedly choose two current numbers $a,b$, delete them, and insert $|a-b|$. Construct $n-1$ operations so the final value is zero, or report impossibility.

反复选择当前数组中的两个数 $a,b$，删除它们并加入 $|a-b|$。构造 $n-1$ 次操作使最终值为0，或判断无解。

## Idea / 思路

### 1. Feasibility is equal partition / 可行性等价于等和划分

Expand the binary operation tree from its final root back to the original leaves. Every internal operation is an absolute difference, so after choosing orientations, the final value can be written as the absolute value of a signed sum
$$\left|\pm x_1\pm x_2\pm\dots\pm x_n\right|.$$
Therefore obtaining zero requires assigning signs so the positive and negative groups have equal sums. Equivalently, some subset must sum to half the total.

Conversely, an equal-sum partition is sufficient; the construction below maintains it until only zero remains. Hence solve a subset-sum problem with target
$$T=\frac12\sum_i x_i.$$
If the total is odd or $T$ is unreachable, print `-1`.

Use a bitset DP:
$$possible_i=possible_{i-1}\ \lor\ (possible_{i-1}\ll x_i).$$
Store every DP row so the chosen subset can be reconstructed backwards. With $n\le1000$ and $T\le500000$, this takes about $63$ MB and uses word-parallel shifts instead of $O(nT)$ scalar transitions.

把最终操作树从根展开回原始叶子。每个内部操作是绝对差，因此在选择每次差的方向后，最终值可写成一个符号和的绝对值：
$$\left|\pm x_1\pm x_2\pm\dots\pm x_n\right|。$$
要得到0，正号组与负号组的总和必须相等；等价地，存在一个子集的和为总和的一半。

反过来，等和划分也充分，下面的构造会一直保持它直到只剩0。因此做目标为
$$T=\frac12\sum_i x_i$$
的子集和。总和为奇数或 $T$ 不可达时输出 `-1`。

使用 bitset DP：
$$possible_i=possible_{i-1}\ \lor\ (possible_{i-1}\ll x_i)。$$
保留每一行 DP，以便从后向前恢复选中子集。$n\le1000$ 且 $T\le500000$，内存约63 MB，并通过机器字并行移位避免标量 $O(nT)$ 转移。

### 2. Maintain two equal-sum multisets / 维护两个等和多重集合

Let multisets $A,B$ be the recovered partition, initially satisfying
$$sum(A)=sum(B).$$
While both are nonempty:

- compare their maximum values;
- suppose $\max A>\max B$;
- take $a=\max A$ and $b=\min B$;
- output operation $(a,b)$ and insert $a-b$ back into $A$.

Because $b\le\max B<a$, the difference is nonnegative. The operation decreases both side sums by exactly $b$:
$$sum(A)'=sum(A)-a+(a-b)=sum(A)-b,$$
$$sum(B)'=sum(B)-b.$$
Thus equality is preserved. If $\max B\ge\max A$, use the symmetric operation with $\max B$ and $\min A$, placing the difference back into $B$.

Eventually one multiset may become empty. Equal sums then force every remaining value in the other multiset to be zero. Combine zeros pairwise until one zero remains. Every iteration reduces the total number of elements by one, so exactly $n-1$ operations are printed.

设恢复出的两个多重集合为 $A,B$，初始满足
$$sum(A)=sum(B)。$$
当两边都非空时：

- 比较两侧最大值；
- 假设 $\max A>\max B$；
- 取 $a=\max A$、$b=\min B$；
- 输出操作 $(a,b)$，并把 $a-b$ 放回 $A$。

因为 $b\le\max B<a$，差非负。该操作让两边总和都恰好减少 $b$：
$$sum(A)'=sum(A)-a+(a-b)=sum(A)-b，$$
$$sum(B)'=sum(B)-b。$$
所以等和不变量保持。若 $\max B\ge\max A$，对称地使用 $\max B$ 与 $\min A$，把差放回 $B$。

最终某一侧可能先变空。此时两侧总和仍相等，所以另一侧剩余元素的总和为0；由于元素非负，它们必然全是0。继续两两合并0，直到只剩一个0。每轮元素总数减少1，因此恰好输出 $n-1$ 次操作。

## Complexity / 复杂度

Bitset DP costs $O(nT/w)$ machine-word operations, where $T\le500000$ and $w$ is the word size. Reconstruction is $O(n)$. The multiset construction uses $O(n\log n)$ time. Memory is $O(nT)$ bits, about $63$ MB at maximum.

Bitset DP 需要 $O(nT/w)$ 次机器字操作，其中 $T\le500000$、$w$ 为机器字位数。恢复子集为 $O(n)$，多重集合构造为 $O(n\log n)$。空间为 $O(nT)$ 位，最大约63 MB。
