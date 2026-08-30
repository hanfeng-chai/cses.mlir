#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cd;
void fft(vector<cd> &a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) { int bit = n >> 1; for (; j & bit; bit >>= 1) j ^= bit; j ^= bit; if (i < j) swap(a[i], a[j]); }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * M_PI / len * (inv ? -1 : 1); cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) { cd w(1); for (int k = 0; k < len / 2; k++) { cd u = a[i + k], v = a[i + k + len / 2] * w; a[i + k] = u + v; a[i + k + len / 2] = u - v; w *= wlen; } }
    }
    if (inv) for (cd &x : a) x /= n;
}
int main() {
    int k, n, m; scanf("%d %d %d", &k, &n, &m);
    vector<ll> A(k + 1, 0), B(k + 1, 0);
    for (int i = 0; i < n; i++) { int w; scanf("%d", &w); A[w]++; }
    for (int i = 0; i < m; i++) { int w; scanf("%d", &w); B[w]++; }
    int sz = 1; while (sz < 2 * (k + 1)) sz <<= 1;
    vector<cd> fa(sz), fb(sz);
    for (int i = 0; i <= k; i++) { fa[i] = A[i]; fb[i] = B[i]; }
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < sz; i++) fa[i] *= fb[i];
    fft(fa, true);
    string out;
    for (int w = 2; w <= 2 * k; w++) { out += to_string((ll)round(fa[w].real())); out += " \n"[w == 2 * k]; }
    cout << out;
}
