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
    int n, m; scanf("%d %d", &n, &m);
    vector<ll> a(n), b(m);
    for (auto &v : a) scanf("%lld", &v);
    for (auto &v : b) scanf("%lld", &v);
    int sz = 1; while (sz < n + m) sz <<= 1;
    vector<cd> A(sz), B(sz);
    for (int i = 0; i < n; i++) A[i] = a[i];
    for (int i = 0; i < m; i++) B[i] = b[m - 1 - i];  // reverse mask: output = conv(signal, reversed mask)
    fft(A, false); fft(B, false);
    for (int i = 0; i < sz; i++) A[i] *= B[i];
    fft(A, true);
    string out;
    for (int t = 0; t < n + m - 1; t++) { out += to_string((ll)round(A[t].real())); out += " \n"[t == n + m - 2]; }
    cout << out;
}
