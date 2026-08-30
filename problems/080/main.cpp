#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int n;
long long dpcur[1 << 10], dpnext[1 << 10];
// Fill one column. `filled` = cells already covered by horizontals from the
// previous column; `out` = horizontals protruding into the next column.
void rec(int r, int filled, int out, long long ways) {
    if (r == n) { dpnext[out] = (dpnext[out] + ways) % MOD; return; }
    if (filled & (1 << r)) { rec(r + 1, filled, out, ways); return; }
    rec(r + 1, filled, out | (1 << r), ways);                 // horizontal domino
    if (r + 1 < n && !(filled & (1 << (r + 1))))              // vertical domino
        rec(r + 2, filled, out, ways);
}
int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < (1 << n); i++) dpcur[i] = 0;
    dpcur[0] = 1;
    for (int c = 0; c < m; c++) {
        for (int i = 0; i < (1 << n); i++) dpnext[i] = 0;
        for (int mask = 0; mask < (1 << n); mask++)
            if (dpcur[mask]) rec(0, mask, 0, dpcur[mask]);
        for (int i = 0; i < (1 << n); i++) dpcur[i] = dpnext[i];
    }
    cout << dpcur[0] << "\n";
}
