# 394 - Same Sum Subsets

## Problem / 题目

Given $n\le40$ positive integers with total sum at most $2^n-2$, find two nonempty disjoint subsets having equal sums.

给定 $n\le40$ 个正整数，且总和不超过 $2^n-2$，求两个非空、互不相交且元素和相等的子集。

## Idea / 思路

### 1. Existence and symmetric difference / 存在性与对称差

There are $2^n-1$ nonempty subsets, but their positive sums lie in at most $2^n-2$ possible integer values. By the pigeonhole principle, two distinct subsets $P,Q$ have the same sum.

They need not be disjoint. Remove their common indices:
$$A=P\setminus Q,\qquad B=Q\setminus P.$$
The sums remain equal. Both are nonempty: if $A$ were empty, positivity and equal sums would force $B$ empty too, contradicting $P\ne Q$.

So it suffices to find any two distinct subsets with equal exact sum.

非空子集共有 $2^n-1$ 个，而它们的正整数和最多只有 $2^n-2$ 种可能值。由鸽巢原理，必有两个不同子集 $P,Q$ 和相等。

它们可能相交，删去公共下标：
$$A=P\setminus Q,\qquad B=Q\setminus P。$$
两边和仍相等。二者都非空：若 $A$ 为空，由元素全为正且两边和相等可推出 $B$ 也为空，这与 $P\ne Q$ 矛盾。

因此只需找到任意两个不同的等和子集。

### 2. Find a duplicated sum by counting / 通过计数定位重复和

Let
$$C(t)=\#\{S\subseteq[1,n]:\sum S\le t\},$$
including the empty subset. If every sum in $[0,t]$ occurred at most once, then $C(t)\le t+1$. Define predicate
$$good(t): C(t)>t+1.$$

At $t=-1$, $C(-1)=0$, so `good` is false. At total sum $T$,
$$C(T)=2^n>T+1$$
because $T\le2^n-2$, so `good` is true.

The predicate need **not** be monotone, but ordinary interval halving still works: maintain endpoints `low` with false and `high` with true. At a midpoint, keep whichever half still has opposite endpoint values. Eventually `high=low+1`. Then
$$C(high)\ge high+2,\qquad C(high-1)\le high,$$
so at least two subsets have sum exactly `high`. This locates a duplicated sum deterministically.

令
$$C(t)=\#\{S\subseteq[1,n]:\sum S\le t\}，$$
其中包含空集。若区间 $[0,t]$ 的每个和最多出现一次，则 $C(t)\le t+1$。定义
$$good(t): C(t)>t+1。$$

$t=-1$ 时 $C(-1)=0$，谓词为假。总和 $T$ 处
$$C(T)=2^n>T+1，$$
因为 $T\le2^n-2$，所以谓词为真。

该谓词**不必单调**，但区间对半缩小仍成立：始终维护左端 `low` 为假、右端 `high` 为真。检查中点后，保留仍具有相反端点值的那一半。最终 `high=low+1`，此时
$$C(high)\ge high+2,\qquad C(high-1)\le high，$$
故恰好和为 `high` 的子集至少有两个。这样就确定性地定位了一个重复和。

### 3. Meet in the middle counting / 折半枚举计数

Split the elements into two halves of at most $20$ elements. Enumerate all subset sums of each half, producing arrays $L,R$ of size at most $2^{20}$. Sort them.

To compute $C(t)$, use two pointers. Traverse $L$ increasingly and keep the largest index $j$ such that
$$L_i+R_j\le t.$$
Then this $L_i$ contributes $j+1$ full subsets. As $L_i$ increases, $j$ only decreases, so one count query is $O(|L|+|R|)$. At most about $40$ interval-halving queries are needed because the total sum is below $2^{40}$.

After finding target sum $s$, use two pointers on the sorted arrays to find two decompositions
$$L_i+R_j=s.$$
The implementation keeps raw subset-sum arrays indexed by masks. Once the required left/right sum groups are known, one linear scan recovers one or two masks realizing each sum. Combine half masks into two full masks, take their symmetric difference, and print the corresponding values.

把元素分成两半，每半至多20个。枚举两半的全部子集和，得到大小至多 $2^{20}$ 的数组 $L,R$，并排序。

计算 $C(t)$ 时使用双指针。按升序遍历 $L_i$，维护最大的 $j$ 使
$$L_i+R_j\le t。$$
该 $L_i$ 贡献 $j+1$ 个完整子集。随着 $L_i$ 增大，$j$ 只会减小，所以一次计数为 $O(|L|+|R|)$。总和小于 $2^{40}$，区间对半最多约40次。

确定目标和 $s$ 后，在排序数组上用双指针寻找两个分解
$$L_i+R_j=s。$$
实现保留按掩码索引的原始子集和数组；知道所需左右和分组后，各线性扫描一次即可恢复对应的一个或两个掩码。把两半掩码拼成两个完整子集，再取对称差并输出数值。

## Complexity / 复杂度

Let $N=2^{\lceil n/2\rceil}\le2^{20}$. Enumeration and sorting cost $O(N\log N)$. Counting uses $O(N\log T)$ time with $\log T\le40$; recovery is $O(N)$. Memory is $O(N)$. The maximum sequential local runtime was about $0.44$ seconds.

令 $N=2^{\lceil n/2\rceil}\le2^{20}$。枚举与排序为 $O(N\log N)$；计数为 $O(N\log T)$，其中 $\log T\le40$；恢复为 $O(N)$。空间复杂度 $O(N)$。最大单进程本地运行时间约0.44秒。
