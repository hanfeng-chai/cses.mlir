# 128 - Salary Queries

## Problem / 题目

Maintain employee salaries under two operations: change one employee's salary, and count employees whose salary falls in a range $[a,b]$.

在两种操作下维护员工薪水：修改某员工薪水；统计薪水落在 $[a,b]$ 内的员工数。

## Idea / 思路

Salaries are up to $10^9$, so **coordinate-compress** all salaries that ever appear (initial and updated values). Keep a Fenwick tree of counts indexed by the compressed salary. Changing a salary is a $-1$ at the old value and $+1$ at the new; a range count is a prefix-count difference between the compressed bounds of $a$ and $b$.

薪水可达 $10^9$，故对所有出现过的薪水（初始与更新值）**离散化**。用一个按压缩薪水为下标的计数树状数组。改薪水即旧值处 $-1$、新值处 $+1$；区间计数为 $a$、$b$ 压缩边界间的前缀计数差。

## Complexity / 复杂度

Every operation is $O(\log n)$ after an $O((n+q)\log)$ compression.

离散化 $O((n+q)\log)$ 后，每个操作 $O(\log n)$。
