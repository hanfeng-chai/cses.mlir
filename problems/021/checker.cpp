#include "testlib.h"
using namespace std;

// 021 Grid Coloring I 是多解题：把每格改成 A/B/C/D，要求 != 原字符且相邻不同。
// 4 种颜色下恒有解，因此正确答案不会是 IMPOSSIBLE。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<string> orig(n);
    for (int i = 0; i < n; i++) orig[i] = inf.readWord();

    string first = ouf.readWord();
    if (upperCase(first) == "IMPOSSIBLE")
        quitf(_wa, "answered IMPOSSIBLE but a coloring always exists");

    vector<string> res(n);
    res[0] = first;
    for (int i = 1; i < n; i++) res[i] = ouf.readWord();
    for (int i = 0; i < n; i++) {
        if ((int)res[i].size() != m) quitf(_wa, "row %d length %d != %d", i, (int)res[i].size(), m);
        for (int j = 0; j < m; j++) {
            char c = res[i][j];
            if (c < 'A' || c > 'D') quitf(_wa, "cell (%d,%d) invalid char '%c'", i, j, c);
            if (c == orig[i][j]) quitf(_wa, "cell (%d,%d) not changed", i, j);
            if (i > 0 && res[i - 1][j] == c) quitf(_wa, "vertical neighbours (%d,%d) equal", i, j);
            if (j > 0 && res[i][j - 1] == c) quitf(_wa, "horizontal neighbours (%d,%d) equal", i, j);
        }
    }
    quitf(_ok, "valid coloring %dx%d", n, m);
}
