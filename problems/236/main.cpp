#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef unsigned long long u64;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<string> g(n);
    char buf[3005];
    for (int i = 0; i < n; i++) { scanf("%s", buf); g[i] = buf; }
    int W = (n + 63) / 64;
    vector<vector<int>> cellsByLetter(k);  // cells per letter in row-major order
    for (int r = 0; r < n; r++)
        for (int j = 0; j < n; j++) { int c = g[r][j] - 'A'; if (c >= 0 && c < k) cellsByLetter[c].push_back(r * n + j); }
    vector<u64> prev((size_t)n * W, 0);  // prev[col] = columns that co-occurred with col (current letter)
    vector<int> ver(n, -1);              // version = letter that last touched prev[col]
    vector<u64> rowmask(W);
    vector<int> C;
    for (int c = 0; c < k; c++) {
        auto &cells = cellsByLetter[c];
        int i = 0, sz = cells.size(); bool found = false;
        while (i < sz && !found) {
            int r = cells[i] / n;
            for (int w = 0; w < W; w++) rowmask[w] = 0;
            C.clear();
            while (i < sz && cells[i] / n == r) { int col = cells[i] % n; C.push_back(col); rowmask[col >> 6] |= 1ULL << (col & 63); i++; }
            for (int col : C) {  // does col share another column with a previous row of this letter?
                if (ver[col] != c) continue;
                u64 *pa = &prev[(size_t)col * W];
                int cw = col >> 6; u64 cb = 1ULL << (col & 63);
                for (int w = 0; w < W; w++) { u64 x = pa[w] & rowmask[w]; if (w == cw) x &= ~cb; if (x) { found = true; break; } }
                if (found) break;
            }
            if (!found)
                for (int col : C) {
                    u64 *pa = &prev[(size_t)col * W];
                    if (ver[col] != c) { memset(pa, 0, W * 8); ver[col] = c; }
                    for (int w = 0; w < W; w++) pa[w] |= rowmask[w];
                }
        }
        puts(found ? "YES" : "NO");
    }
}
