# 397 - Stick Divisions

## Problem / 题目

Split a stick of length $x$ into $n$ sticks of given target lengths $d_1,\dots,d_n$ (summing to $x$); each split of a stick costs its current length. Minimize the total cost.

把一根长度为 $x$ 的木棒分割成 $n$ 根给定长度 $d_1,\dots,d_n$ 的木棒（总和为 $x$）；每次把一根木棒切成两根的代价是被切木棒当前的长度。求最小总代价。

## Idea / 思路

Splitting is the reverse of merging: reading the sequence of splits backwards, we start from the $n$ leaves (target lengths) and repeatedly *merge* two current sticks into one (of length equal to their sum), until a single stick of length $x$ remains — and each merge's cost equals the merged length, exactly matching a split's cost. So the total cost is the sum, over every **internal node** of the resulting binary merge tree, of that node's value (= sum of its subtree's leaves).

Minimizing the sum of internal-node values over all binary merge trees with fixed leaf multiset is *exactly* the classical **Huffman coding** problem (there, one minimizes $\sum (\text{leaf weight})\times(\text{depth})$, which telescopes to the same "sum of internal node values" objective). The optimal strategy is Huffman's greedy: repeatedly take the two smallest current values, merge them (cost += their sum), and put the sum back into the pool, using a min-heap.

*Sanity check* on the sample ($x=8$, sticks $[2,3,3]$): merge $2+3=5$ (cost 5), then merge $5+3=8$ (cost 8); total $5+8=13$, matching the expected output — this also matches the sample's own explanation (splitting $8\to3+5\to$ then $5\to2+3$, total cost $8+5=13$), just executed in the reverse (bottom-up) direction.

分割是合并的逆过程：把分割序列倒过来看，从 $n$ 个叶子（目标长度）出发，反复把当前两根木棒**合并**成一根（长度为二者之和），直到只剩一根长度为 $x$ 的木棒——每次合并的代价等于合并后的长度，恰好对应一次分割的代价。所以总代价等于所得二叉合并树中**每个内部节点**的值（=其子树所有叶子之和）之和。

在叶子多重集固定的情况下，让所有二叉合并树的内部节点值之和最小，正是经典的**Huffman 编码**问题（那里最小化的是 $\sum(\text{叶子权重})\times(\text{深度})$，可以证明与"内部节点值之和"这一目标是等价的、可以互相telescope）。最优策略就是 Huffman 贪心：反复取出当前最小的两个值，合并它们（代价累加二者之和），把和放回集合中，用小顶堆维护。

*样例验证*（$x=8$，木棒 $[2,3,3]$）：合并 $2+3=5$（代价5），再合并 $5+3=8$（代价8）；总代价 $5+8=13$，与期望输出一致——这也与样例自身的说明（先把 $8$ 分成 $3+5$，再把 $5$ 分成 $2+3$，代价 $8+5=13$）吻合，只是方向相反（自底向上执行）。

## Complexity / 复杂度

Standard Huffman via a min-heap: $O(n\log n)$ for $n\le 2\times 10^5$.

标准 Huffman，用小顶堆实现：$O(n\log n)$，$n\le2\times10^5$ 内很快。
