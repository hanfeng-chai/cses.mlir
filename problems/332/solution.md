# 332 - Counting Bishops

## Problem / 题目

Count the ways to place $k$ bishops on an $n\times n$ chessboard so that no two attack each other (share a diagonal), modulo $10^9+7$.

求在 $n\times n$ 棋盘上放 $k$ 个互不攻击（不共享对角线）的象的方案数，对 $10^9+7$ 取模。

## Idea / 思路

**Step 1 — split by color.** For a cell $(i,j)$, both diagonal indices $i-j$ ("\\"-diagonal) and $i+j$ ("/"-diagonal) always have the *same parity* (since $(i+j)-(i-j)=2j$ is even). So every "\\" or "/" diagonal is entirely made of cells of one color in the usual checkerboard coloring (color = parity of $i+j$). Consequently a bishop on a white cell can *never* share a diagonal with a bishop on a black cell — the two colors are completely independent sub-boards! If $f_{\text{white}}(k)$ and $f_{\text{black}}(k)$ count ways to place $k$ non-attacking bishops using only cells of one color, the answer for the whole board is the convolution
$$f(k)=\sum_{k_1+k_2=k} f_{\text{white}}(k_1)\cdot f_{\text{black}}(k_2).$$

**Step 2 — one color reduces to a "staircase rook" problem.** Fix one color. List the lengths of its "/"-diagonals (diagonals with $i+j$ of that parity); a short computation shows these lengths, sorted, always form a **nested/pyramid** pattern (e.g. for $n=5$ one color's "/"-diagonal lengths sorted are $[1,1,3,3,5]$, and remarkably its "\\"-diagonal lengths sorted are the *same* multiset). Geometrically this is because a monochromatic sub-board, once you rotate the picture $45°$, becomes a diamond, whose "rows" and "columns" (the two diagonal directions) are two copies of the same staircase shape, nested inside one another when sorted by length. Placing bishops with no shared diagonal in either direction, restricted to one color, is then equivalent to placing non-attacking **rooks** on this staircase board — and thanks to the nesting, when the diagonals are processed in increasing length order $L_1\le L_2\le\dots\le L_m$, any $j$ rooks already placed on shorter diagonals occupy $j$ columns that are *automatically* among the $L_i$ available columns of the next, longer diagonal. So there are exactly $L_i-j$ free columns left for a new rook:
$$dp[j+1]\mathrel{+}=dp[j]\cdot(L_i-j).$$
This is exactly the `poly` function: it sorts one color's list of "/"-diagonal lengths and runs this staircase DP, producing, for that color, the number of ways to place $0,1,2,\dots$ non-attacking bishops.

**Step 3 — combine.** Running `poly` once for the diagonals with $i+j$ odd and once for $i+j$ even gives `pa` and `pb`; the answer for $k$ bishops is $\sum_i pa[i]\cdot pb[k-i]$.

*Sanity check ($n=5$):* the odd-color "/"-diagonal lengths sorted are $[2,2,4,4]$, giving `pa = [1,12,38,32,4]` for $0..4$ bishops; the even-color lengths sorted are $[1,1,3,3,5]$, giving `pb = [1,13,46,46,8,0]` for $0..5$ bishops. For $k=4$: $1\cdot8+12\cdot46+38\cdot46+32\cdot13+4\cdot1=8+552+1748+416+4=2728$ — matching the sample answer exactly.

**第一步——按颜色拆分。** 对格子 $(i,j)$，两种对角线编号 $i-j$（"\\" 方向）与 $i+j$（"/" 方向）的奇偶性**总是相同**（因为 $(i+j)-(i-j)=2j$ 是偶数）。所以每条 "\\" 或 "/" 对角线上的格子，在通常的棋盘黑白染色（颜色=$i+j$ 的奇偶性）下，颜色**完全一致**。于是白格上的象永远不可能和黑格上的象共享对角线——两种颜色是完全独立的两个子棋盘！若 $f_{\text{白}}(k)$、$f_{\text{黑}}(k)$ 分别是只用某一色格子放 $k$ 个互不攻击象的方案数，则整棋盘的答案是卷积
$$f(k)=\sum_{k_1+k_2=k} f_{\text{白}}(k_1)\cdot f_{\text{黑}}(k_2)。$$

**第二步——单一颜色化为"楼梯型车"问题。** 固定一种颜色，列出它所有 "/" 对角线的长度；可以验证排序后这些长度总呈现**嵌套/金字塔**形态（例如 $n=5$ 时某一色 "/" 对角线排序后长度为 $[1,1,3,3,5]$，而神奇的是同一色 "\\" 对角线排序后长度是**同一个**多重集）。几何上看，这是因为把某一色的子棋盘旋转 $45°$ 后会变成一个菱形，它的"行"与"列"（两个对角线方向）恰好是同一个楼梯形状的两份拷贝，按长度排序后彼此嵌套。在单一颜色内、两个方向都不能共享对角线地放象，就等价于在这个楼梯形棋盘上放互不攻击的**车**——而正因为这种嵌套关系，把对角线按长度从小到大排序 $L_1\le L_2\le\dots\le L_m$ 处理时，之前已经放在较短对角线上的 $j$ 个车所占的列，**必然**都落在下一条更长对角线的 $L_i$ 个可用列之内。所以新对角线上恰好剩下 $L_i-j$ 个空列可选：
$$dp[j+1]\mathrel{+}=dp[j]\cdot(L_i-j)。$$
这正是 `poly` 函数所做的：对某一色的 "/" 对角线长度列表排序后跑这个楼梯 DP，得到该颜色下放 $0,1,2,\dots$ 个互不攻击象的方案数。

**第三步——合并。** 对 $i+j$ 为奇的对角线跑一次 `poly` 得 `pa`，对 $i+j$ 为偶的跑一次得 `pb`；放 $k$ 个象的答案就是 $\sum_i pa[i]\cdot pb[k-i]$。

*验证（$n=5$）：* 奇色 "/" 对角线排序长度为 $[2,2,4,4]$，得 `pa = [1,12,38,32,4]`（放 $0..4$ 个）；偶色长度为 $[1,1,3,3,5]$，得 `pb = [1,13,46,46,8,0]`（放 $0..5$ 个）。当 $k=4$ 时：$1\cdot8+12\cdot46+38\cdot46+32\cdot13+4\cdot1=8+552+1748+416+4=2728$，与样例答案完全一致。

## Complexity / 复杂度

Building each color's diagonal-length list is $O(n)$; the staircase DP for one color is $O(n^2)$ in the worst case (roughly $n/2$ diagonals, DP array up to size $n/2$); the final convolution is $O(n)$. Overall $O(n^2)$, i.e. about $2.5\times10^5$ operations for $n\le500$.

构造每种颜色的对角线长度列表是 $O(n)$；单色楼梯 DP 最坏 $O(n^2)$（约 $n/2$ 条对角线，DP 数组大小约 $n/2$）；最后卷积 $O(n)$。总体 $O(n^2)$，$n\le500$ 时约 $2.5\times10^5$ 次操作。
