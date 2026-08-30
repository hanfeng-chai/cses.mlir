# 236 - Corner Subgrid Check

## Problem / 题目
For each of $k$ letters, decide whether some subgrid (height and width $\ge 2$) has all four corners equal to that letter.

对每个（共 $k$ 个）字母，判断是否存在某个子网格（高、宽 $\ge 2$）四角都是该字母。

## Idea / 思路
For a fixed letter, process rows one by one; in each row collect the columns containing that letter and mark every pair of such columns. If a column pair has already been marked (from an earlier row), the two rows and two columns form a valid subgrid. A timestamp array indexed by column pair avoids resetting between letters. If no answer exists, the number of distinct marked pairs is bounded by $\binom{n}{2}$, keeping the total work small.

对固定字母，逐行处理；每行收集含该字母的列并标记每一对这样的列。若某列对此前已被标记（来自更早的行），则这两行两列构成合法子网格。以列对为下标的时间戳数组避免按字母重置。若无解，被标记的不同列对数不超过 $\binom{n}{2}$，故总工作量受控。

## Complexity / 复杂度
$O(k\,n^2)$ worst case. 最坏 $O(k\,n^2)$。
