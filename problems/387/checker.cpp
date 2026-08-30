#include "testlib.h"
using namespace std;

// 387 Grid Puzzle I 是多解题：只要满足所有行列和约束的 0/1 矩阵都算对；
// 如果裁判判定不可能，参赛输出也必须是 -1。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> a(n), b(n);
    for (auto &v : a) v = inf.readInt();
    for (auto &v : b) v = inf.readInt();

    string jFirst = ans.readWord();
    bool jImpossible = (jFirst == "-1");

    string pFirst = ouf.readWord();
    bool pImpossible = (pFirst == "-1");

    if (jImpossible != pImpossible) {
        if (jImpossible) quitf(_wa, "jury says IMPOSSIBLE, but participant gives a grid");
        else quitf(_wa, "participant says IMPOSSIBLE, but a valid grid exists");
    }
    if (jImpossible) { quitf(_ok, "correctly IMPOSSIBLE"); }

    vector<string> grid(n);
    grid[0] = pFirst;
    for (int i = 1; i < n; i++) grid[i] = ouf.readWord();

    vector<int> rowSum(n, 0), colSum(n, 0);
    for (int i = 0; i < n; i++) {
        if ((int)grid[i].size() != n)
            quitf(_pe, "row %d has length %d, expected %d", i + 1, (int)grid[i].size(), n);
        for (int j = 0; j < n; j++) {
            char ch = grid[i][j];
            if (ch != 'X' && ch != '.')
                quitf(_pe, "invalid character '%c' at (%d,%d)", ch, i + 1, j + 1);
            if (ch == 'X') { rowSum[i]++; colSum[j]++; }
        }
    }
    for (int i = 0; i < n; i++)
        if (rowSum[i] != a[i]) quitf(_wa, "row %d has sum %d, expected %d", i + 1, rowSum[i], a[i]);
    for (int j = 0; j < n; j++)
        if (colSum[j] != b[j]) quitf(_wa, "column %d has sum %d, expected %d", j + 1, colSum[j], b[j]);

    quitf(_ok, "valid grid satisfying all row/column sums");
}
