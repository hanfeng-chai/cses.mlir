#include "testlib.h"
using namespace std;

// 381 Coin Grid 是多解题：任何大小等于最优解的行/列覆盖都算对。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<string> g(n);
    for (auto &row : g) row = inf.readWord();

    int jk = ans.readInt();
    int pk = ouf.readInt();
    if (pk != jk) quitf(_wa, "answer %d, but optimal is %d", pk, jk);

    vector<bool> rowSel(n, false), colSel(n, false);
    for (int i = 0; i < pk; i++) {
        int t = ouf.readInt(1, 2, "move type");
        int idx = ouf.readInt(1, n, "index");
        if (t == 1) {
            if (rowSel[idx - 1]) quitf(_wa, "row %d selected more than once", idx);
            rowSel[idx - 1] = true;
        } else {
            if (colSel[idx - 1]) quitf(_wa, "column %d selected more than once", idx);
            colSel[idx - 1] = true;
        }
    }

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (g[r][c] == 'o' && !rowSel[r] && !colSel[c])
                quitf(_wa, "coin at (%d,%d) not removed by any selected row/column", r + 1, c + 1);

    quitf(_ok, "valid minimum cover of size %d", pk);
}
