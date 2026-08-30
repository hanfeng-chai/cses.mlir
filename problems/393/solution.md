# 393 - Minimum Cost Pairs

## Problem / 题目

For every $k=1,2,\dots,\lfloor n/2\rfloor$, choose $k$ disjoint pairs minimizing the sum of absolute differences, and output the minimum cost.

对每个 $k=1,2,\dots,\lfloor n/2\rfloor$，选择 $k$ 个互不相交的数对，使绝对差之和最小，并输出该最小代价。

## Idea / 思路

Sort the values as $a_0\le a_1\le\dots\le a_{n-1}$. There is an optimal solution using only pairs of adjacent currently available sorted points. If a pair spans an unused interior point, replacing one endpoint by a closer interior point cannot increase cost; uncrossing two nested/crossing pairs similarly yields adjacent noncrossing pairs. Therefore the problem becomes minimum-cardinality matching on a path whose edge weights are
$$w_i=a_i-a_{i-1}\qquad(1\le i<n).$$
We need the minimum weight matching of every cardinality.

A path admits a greedy contraction algorithm. Keep all current edge weights in a min-heap and a doubly linked list of active edges. Repeatedly:

1. extract the minimum active edge $e$ with weight $w$;
2. add $w$ to the running answer — this gives the next matching cardinality optimum;
3. let its active neighboring edges have weights $w_L,w_R$ (use infinite sentinels at the path ends);
4. remove the two neighboring edges and replace $e$ by a contracted pseudo-edge of weight
   $$w_L+w_R-w.$$

Why this replacement? After selecting middle edge $e$, a future way to increase the matching cardinality locally is to **replace** $e$ by both adjacent edges. The old solution paid $w$; the replacement pays $w_L+w_R$, so its incremental cost is exactly $w_L+w_R-w$. Contracting the three edges into one pseudo-edge records that alternative without keeping the entire earlier matching.

This operation preserves the set of possible incremental costs for larger matching cardinalities. Inductively, extracting the globally smallest available increment yields the next difference
$$OPT(k)-OPT(k-1),$$
so cumulative extracted weights are $OPT(1),OPT(2),\dots$. Lazy deletion handles heap entries whose edge was removed by a neighboring contraction.

将数值排序为 $a_0\le a_1\le\dots\le a_{n-1}$。存在一个最优解只使用当前排序点列中的相邻点配对：若某对跨过一个未使用内点，把端点换成更近的内点不会增加代价；两组嵌套或交叉配对也可通过交换端点消除。因此问题变成路径上的固定基数最小权匹配，边权为
$$w_i=a_i-a_{i-1}\qquad(1\le i<n)。$$
需要一次求出所有匹配基数的最小权。

路径可用贪心收缩算法。把当前所有边权放入小顶堆，并用双向链表维护活动边。反复执行：

1. 取最小活动边 $e$，权为 $w$；
2. 把 $w$ 加入累计答案，得到下一个匹配基数的最优值；
3. 设其左右活动邻边权为 $w_L,w_R$（路径端点使用无穷哨兵）；
4. 删除左右邻边，并把 $e$ 更新为权值
   $$w_L+w_R-w$$
   的收缩伪边。

为什么是这个新权？选中中间边 $e$ 后，将来若要在这个局部把匹配数增加1，可以把 $e$ **替换**成左右两条邻边。旧方案支付 $w$，新方案支付 $w_L+w_R$，因此额外代价恰好是 $w_L+w_R-w$。把三条边收缩成一条伪边，就能记录这个替代方案，而无需保留完整历史匹配。

该操作保持了后续所有更大基数可用的增量代价集合。归纳地，每次取出的全局最小增量就是
$$OPT(k)-OPT(k-1)，$$
所以累计取出的权值依次为 $OPT(1),OPT(2),\dots$。堆中被邻居收缩删除的旧边用懒删除跳过。

## Complexity / 复杂度

Sorting is $O(n\log n)$. There are $\lfloor n/2\rfloor$ contractions, each with $O(\log n)$ heap work, so total time is $O(n\log n)$ and memory is $O(n)$.

排序为 $O(n\log n)$。共有 $\lfloor n/2\rfloor$ 次收缩，每次堆操作 $O(\log n)$，总时间 $O(n\log n)$，空间 $O(n)$。
