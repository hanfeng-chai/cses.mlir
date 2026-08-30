# 026 - Apartments

## Problem / 题目

There are $n$ applicants and $m$ apartments. An applicant with desired size $x$ accepts any apartment whose size lies in $[x-k, x+k]$. Match applicants to apartments to maximise the number of satisfied applicants.

有 $n$ 个申请人和 $m$ 套公寓。期望面积为 $x$ 的申请人能接受面积在 $[x-k, x+k]$ 内的任意公寓。把申请人与公寓配对，使满足的申请人数最多。

## Idea / 思路

Sort both the desired sizes and the apartment sizes, then sweep with two pointers. If the current applicant and apartment match (their difference is $\le k$), pair them and advance both pointers. Otherwise, if the apartment is too small ($b < a-k$) advance the apartment pointer, and if it is too large ($a+k < b$, so this applicant can use neither it nor any larger one) advance the applicant pointer. This greedy pairing is optimal.

把期望面积和公寓面积都排序，然后用双指针扫描。若当前申请人与公寓匹配（差 $\le k$），配对并同时前移两个指针。否则，若公寓太小（$b < a-k$）就前移公寓指针；若公寓太大（$a+k < b$，则该申请人连它和更大的都用不了）就前移申请人指针。这个贪心配对是最优的。

## Complexity / 复杂度

Two sorts plus a linear sweep give $O(n \log n + m \log m)$.

两次排序加一次线性扫描，为 $O(n \log n + m \log m)$。
