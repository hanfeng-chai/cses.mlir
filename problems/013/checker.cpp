#include "testlib.h"
using namespace std;

// 013 Gray Code 是多解题：任意合法格雷码——2^n 行，每行 n 位，
// 相邻两行恰好相差 1 位，且 2^n 个串互不相同。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int total = 1 << n;
    vector<string> g(total);
    for (int i = 0; i < total; i++) {
        g[i] = ouf.readWord();
        if ((int)g[i].size() != n) quitf(_wa, "line %d: length %d != %d", i, (int)g[i].size(), n);
        for (char c : g[i]) if (c != '0' && c != '1') quitf(_wa, "line %d: non-bit char", i);
    }
    for (int i = 1; i < total; i++) {
        int d = 0;
        for (int b = 0; b < n; b++) d += (g[i][b] != g[i - 1][b]);
        if (d != 1) quitf(_wa, "lines %d and %d differ in %d bits", i - 1, i, d);
    }
    set<string> seen(g.begin(), g.end());
    if ((int)seen.size() != total) quitf(_wa, "codes are not all distinct");
    quitf(_ok, "valid gray code (n=%d)", n);
}
