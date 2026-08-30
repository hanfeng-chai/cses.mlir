# 253 - Signal Processing

## Problem / 题目
Slide a mask across a signal; at each alignment output the sum of products of overlapping values.

让掩码在信号上滑动；在每个对齐位置输出重叠值乘积之和。

## Idea / 思路
Sliding-window sums of products are a cross-correlation, which equals the convolution of the signal with the reversed mask. Computing that convolution with FFT yields all $n+m-1$ outputs at once.

滑动窗口乘积和是一种互相关，等于信号与反转掩码的卷积。用 FFT 计算该卷积可一次得到全部 $n+m-1$ 个输出。

## Complexity / 复杂度
$O((n+m)\log(n+m))$. $O((n+m)\log(n+m))$。
