#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int x = inf.readInt(), y = inf.readInt();
    vector<pair<int, int>> pos(65, {-1, -1});
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            int v = ouf.readInt(1, 64);
            if (pos[v].first != -1) quitf(_wa, "move number %d repeated", v);
            pos[v] = {i, j};
        }
    if (pos[1] != make_pair(y - 1, x - 1)) quitf(_wa, "move 1 is not at the start square");
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2}, dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int k = 1; k < 64; k++) {
        auto [r1, c1] = pos[k];
        auto [r2, c2] = pos[k + 1];
        bool ok = false;
        for (int d = 0; d < 8; d++) if (r1 + dr[d] == r2 && c1 + dc[d] == c2) ok = true;
        if (!ok) quitf(_wa, "moves %d and %d are not a knight move apart", k, k + 1);
    }
    quitf(_ok, "valid knight's tour");
}
