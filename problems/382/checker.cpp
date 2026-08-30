#include "testlib.h"
using namespace std;

// 382 Grid Coloring II 是多解题：任何满足"每格都变了、且相邻格不同色"的网格都算对；
// 若裁判判定不可能，参赛输出也必须是 IMPOSSIBLE。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> orig(n);
    for (auto &row : orig) row = inf.readWord();

    string jFirst = ans.readWord();
    bool jImpossible = (jFirst == "IMPOSSIBLE");
    string pFirst = ouf.readWord();
    bool pImpossible = (pFirst == "IMPOSSIBLE");

    if (jImpossible != pImpossible) {
        if (jImpossible) quitf(_wa, "jury says IMPOSSIBLE, but participant gives a grid");
        else quitf(_wa, "participant says IMPOSSIBLE, but a valid grid exists");
    }
    if (jImpossible) { quitf(_ok, "correctly IMPOSSIBLE"); }

    vector<string> g(n);
    g[0] = pFirst;
    for (int i = 1; i < n; i++) g[i] = ouf.readWord();

    for (int i = 0; i < n; i++) {
        if ((int)g[i].size() != m)
            quitf(_pe, "row %d has length %d, expected %d", i + 1, (int)g[i].size(), m);
        for (int j = 0; j < m; j++) {
            char ch = g[i][j];
            if (ch != 'A' && ch != 'B' && ch != 'C')
                quitf(_pe, "invalid character '%c' at (%d,%d)", ch, i + 1, j + 1);
            if (ch == orig[i][j])
                quitf(_wa, "cell (%d,%d) unchanged (still '%c')", i + 1, j + 1, ch);
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (i + 1 < n && g[i][j] == g[i + 1][j])
                quitf(_wa, "cells (%d,%d) and (%d,%d) share color '%c'", i + 1, j + 1, i + 2, j + 1, g[i][j]);
            if (j + 1 < m && g[i][j] == g[i][j + 1])
                quitf(_wa, "cells (%d,%d) and (%d,%d) share color '%c'", i + 1, j + 1, i + 1, j + 2, g[i][j]);
        }

    quitf(_ok, "valid recoloring");
}
