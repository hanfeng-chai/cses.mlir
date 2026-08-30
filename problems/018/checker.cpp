#include "testlib.h"
using namespace std;

// 018 Raab Game I 是多解题：给出任意一种达成给定比分的对局。
// 可行 <=> a+b<=n 且 (a==0)==(b==0)。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int tc = 1; tc <= t; tc++) {
        int n = inf.readInt(), a = inf.readInt(), b = inf.readInt();
        bool possible = (a + b <= n) && ((a == 0) == (b == 0));
        string v = upperCase(ouf.readWord());
        if (v == "NO") {
            if (possible) quitf(_wa, "test %d: NO but a game exists (n=%d a=%d b=%d)", tc, n, a, b);
            continue;
        }
        if (v != "YES") quitf(_wa, "test %d: expected YES or NO, got '%s'", tc, v.c_str());
        if (!possible) quitf(_wa, "test %d: YES but no game exists (n=%d a=%d b=%d)", tc, n, a, b);
        vector<int> P(n), Q(n);
        for (int i = 0; i < n; i++) P[i] = ouf.readInt(1, n, "P_i");
        for (int i = 0; i < n; i++) Q[i] = ouf.readInt(1, n, "Q_i");
        vector<char> sp(n + 1, 0), sq(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (sp[P[i]]) quitf(_wa, "test %d: P is not a permutation", tc);
            sp[P[i]] = 1;
        }
        for (int i = 0; i < n; i++) {
            if (sq[Q[i]]) quitf(_wa, "test %d: Q is not a permutation", tc);
            sq[Q[i]] = 1;
        }
        int ca = 0, cb = 0;
        for (int i = 0; i < n; i++) {
            if (P[i] > Q[i]) ca++;
            else if (P[i] < Q[i]) cb++;
        }
        if (ca != a || cb != b) quitf(_wa, "test %d: scores (%d,%d) != (%d,%d)", tc, ca, cb, a, b);
    }
    quitf(_ok, "all %d games valid", t);
}
