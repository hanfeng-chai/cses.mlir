# 295 - Nearest Shops

## Problem / 题目
For each city, find the distance to the nearest shop located in a *different* city, or $-1$ if none exists.

对每座城市，求到另一座（不同城市）最近商店的距离，若不存在输出 $-1$。

## Idea / 思路
Run a multi-source BFS from all shops, but store for each node its two nearest sources coming from **distinct** roots. A non-shop city's answer is its nearest source; a shop city must use the second-nearest (since its own source is at distance $0$). The two-label BFS processes nodes in non-decreasing distance, accepting at most two labels with different roots per node.

从所有商店做多源 BFS，但每个结点保存来自**不同根**的两个最近源。非商店城市答案取最近源；商店城市须取次近源（因自身源距离为 $0$）。双标号 BFS 按距离非降处理，每点至多接受两个不同根的标号。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
