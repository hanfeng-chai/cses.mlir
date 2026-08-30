#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Labyrinth: validate a shortest path string from A to B.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<string> g(n);
    for (int i = 0; i < n; i++) g[i] = inf.readWord();
    int sx = 0, sy = 0, ex = 0, ey = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'A') { sx = i; sy = j; }
            if (g[i][j] == 'B') { ex = i; ey = j; }
        }
    string jw = ans.readWord(), pw = ouf.readWord();
    if (jw == "NO") {
        if (pw != "NO") quitf(_wa, "expected NO, found %s", pw.c_str());
        quitf(_ok, "NO");
    }
    if (pw != "YES") quitf(_wa, "expected YES, found %s", pw.c_str());
    long long jlen = ans.readLong(), plen = ouf.readLong();
    if (plen != jlen) quitf(_wa, "length differs: expected %lld, found %lld", jlen, plen);
    string path = plen > 0 ? ouf.readWord() : "";
    if ((long long)path.size() != plen) quitf(_wa, "path length %d != stated %lld", (int)path.size(), plen);
    int x = sx, y = sy;
    for (char c : path) {
        if (c == 'U') x--; else if (c == 'D') x++; else if (c == 'L') y--; else if (c == 'R') y++;
        else quitf(_wa, "bad move char %c", c);
        if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == '#') quitf(_wa, "move leaves floor at (%d,%d)", x, y);
    }
    if (x != ex || y != ey) quitf(_wa, "path ends at (%d,%d), not B", x, y);
    quitf(_ok, "shortest path length %lld", plen);
}
