# 389 - Bit Substrings

## Problem / 题目

For every $k=0,1,\dots,n$, count nonempty substrings of a binary string containing exactly $k$ ones.

对二进制串的每个 $k=0,1,\dots,n$，统计恰好包含 $k$ 个1的非空子串数量。

## Idea / 思路

Let prefix sum $p_i$ be the number of ones in the first $i$ characters, for $i=0,\dots,n$. A substring $[l,r)$ contains exactly $k$ ones iff
$$p_r-p_l=k.$$
Let $f_t$ be the number of prefixes whose sum equals $t$.

For $k>0$, if $p_r=p_l+k$, then automatically $r>l$ because prefix sums are nondecreasing and a larger sum cannot occur earlier. Therefore
$$answer[k]=\sum_t f_t f_{t+k}\qquad(k>0).$$
This is the cross-correlation of the frequency array with itself.

For $k=0$, both endpoints have the same prefix sum, but their order matters only by choosing two distinct prefixes. Hence
$$answer[0]=\sum_t\binom{f_t}{2}.$$

To compute all positive $k$ simultaneously, convolve
$$A[i]=f_i,\qquad B[n-i]=f_i.$$
At convolution index $n+k$:
$$[z^{n+k}]A(z)B(z)=\sum_i f_i f_{i-k}=\sum_t f_{t+k}f_t=answer[k].$$

The maximum answer is $n(n+1)/2\approx2\cdot10^{10}$, larger than a single common NTT modulus. Use two NTT-friendly primes:
$$M_1=998244353,\qquad M_2=1004535809,$$
both with primitive root $3$. Compute the convolution modulo each prime, then reconstruct the exact integer with CRT:
$$x=r_1+M_1\left((r_2-r_1)M_1^{-1}\bmod M_2\right).$$
Since $M_1M_2>10^{18}$, far above every possible answer, this reconstruction is unique and exact. This avoids floating-point rounding concerns from FFT.

令前缀和 $p_i$ 表示前 $i$ 个字符中的1数量，$i=0,\dots,n$。子串 $[l,r)$ 恰好有 $k$ 个1，当且仅当
$$p_r-p_l=k。$$
令 $f_t$ 为前缀和等于 $t$ 的前缀数量。

当 $k>0$ 时，若 $p_r=p_l+k$，由于前缀和单调不减，较大的前缀和不可能更早出现，所以自动有 $r>l$。因此
$$answer[k]=\sum_t f_t f_{t+k}\qquad(k>0)。$$
这就是频率数组的自相关。

当 $k=0$ 时，两个端点前缀和相等，只需从同组前缀中选择两个不同位置：
$$answer[0]=\sum_t\binom{f_t}{2}。$$

为了同时求所有正 $k$，构造
$$A[i]=f_i,\qquad B[n-i]=f_i$$
并做卷积。卷积下标 $n+k$ 的系数为
$$[z^{n+k}]A(z)B(z)=\sum_i f_i f_{i-k}=\sum_t f_{t+k}f_t=answer[k]。$$

最大答案可达 $n(n+1)/2\approx2\cdot10^{10}$，超过一个常用NTT模数。使用两个NTT友好素数
$$M_1=998244353,\qquad M_2=1004535809，$$
二者原根均为3。分别计算两次模卷积，再用CRT恢复精确整数：
$$x=r_1+M_1\left((r_2-r_1)M_1^{-1}\bmod M_2\right)。$$
因为 $M_1M_2>10^{18}$，远大于任何可能答案，恢复结果唯一且精确，也避免了浮点FFT的舍入风险。

## Complexity / 复杂度

Two NTT convolutions of length $O(n)$ take $O(n\log n)$ time and $O(n)$ memory.

两次长度为 $O(n)$ 的NTT卷积共需 $O(n\log n)$ 时间和 $O(n)$ 空间。
