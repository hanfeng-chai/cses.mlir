#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    int M = 1; while (M < n) M <<= 1;
    vector<int> g(M, 0);
    for (int i = 0; i < n; i++) scanf("%d", &g[i]);
    for (int b = 0; (1 << b) < M; b++)
        for (int mask = 0; mask < M; mask++) if (mask >> b & 1) g[mask] ^= g[mask ^ (1 << b)];  // submask xor (SOS)
    string out;
    for (int r = 0; r < n; r++) { out += to_string(g[r]); out += " \n"[r == n - 1]; }  // leftmost of row r = xor over i submask of r
    cout << out;
}
