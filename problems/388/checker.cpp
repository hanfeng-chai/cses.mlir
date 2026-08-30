#include "testlib.h"
using namespace std;

// 388 Grid Puzzle II 是多解题：只要满足行列和约束、且收集到的金币总数达到裁判的最优值，
// 具体选择哪些格子都算对；若裁判判定不可能，参赛输出也必须是 -1。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> a(n), b(n);
    for (auto &v : a) v = inf.readInt();
    for (auto &v : b) v = inf.readInt();
    vector<vector<long long>> c(n, vector<long long>(n));
    for (auto &row : c) for (auto &v : row) v = inf.readLong();

    string jFirst = ans.readWord();
    bool jImpossible = (jFirst == "-1");
    string pFirst = ouf.readWord();
    bool pImpossible = (pFirst == "-1");

    if (jImpossible != pImpossible) {
        if (jImpossible) quitf(_wa, "jury says IMPOSSIBLE, but participant gives a grid");
        else quitf(_wa, "participant says IMPOSSIBLE, but a valid grid exists");
    }
    if (jImpossible) { quitf(_ok, "correctly IMPOSSIBLE"); }

    long long jK = std::stoll(jFirst);
    long long pK = std::stoll(pFirst);
    if (pK != jK) quitf(_wa, "reported total %lld, but optimal is %lld", pK, jK);

    vector<string> grid(n);
    for (int i = 0; i < n; i++) grid[i] = ouf.readWord();

    vector<int> rowSum(n, 0), colSum(n, 0);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        if ((int)grid[i].size() != n)
            quitf(_pe, "row %d has length %d, expected %d", i + 1, (int)grid[i].size(), n);
        for (int j = 0; j < n; j++) {
            char ch = grid[i][j];
            if (ch != 'X' && ch != '.')
                quitf(_pe, "invalid character '%c' at (%d,%d)", ch, i + 1, j + 1);
            if (ch == 'X') { rowSum[i]++; colSum[j]++; total += c[i][j]; }
        }
    }
    for (int i = 0; i < n; i++)
        if (rowSum[i] != a[i]) quitf(_wa, "row %d has sum %d, expected %d", i + 1, rowSum[i], a[i]);
    for (int j = 0; j < n; j++)
        if (colSum[j] != b[j]) quitf(_wa, "column %d has sum %d, expected %d", j + 1, colSum[j], b[j]);
    if (total != jK) quitf(_wa, "grid collects %lld coins, but claimed %lld", total, jK);

    quitf(_ok, "valid grid collecting %lld coins", total);
}
