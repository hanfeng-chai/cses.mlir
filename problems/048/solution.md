# 048 - Tasks and Deadlines

## Problem / 题目

Process all tasks one after another starting at time $0$. A task with deadline $d$ finished at time $f$ gives reward $d - f$. Maximise the total reward.

从时刻 $0$ 开始依次处理所有任务。截止为 $d$、在时刻 $f$ 完成的任务给予奖励 $d - f$。最大化总奖励。

## Idea / 思路

The total reward is $\sum d_i - \sum f_i$; the deadline sum is fixed, so we only need to minimise the sum of finishing times. Finishing times are minimised by the shortest-job-first rule: sort tasks by duration ascending, accumulate the running finish time, and add each $d_i - f_i$.

总奖励是 $\sum d_i - \sum f_i$；截止之和固定，所以只需最小化完成时间之和。完成时间由最短作业优先（SJF）最小化：把任务按时长升序排序，累加当前完成时间，并加上每个 $d_i - f_i$。

## Complexity / 复杂度

Sorting dominates, so the time is $O(n \log n)$.

排序是主要开销，因此时间为 $O(n \log n)$。
