#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    int N = 2 * n + 1;
    vector<char> comp(N + 1, 0);
    for (int i = 2; (long long)i * i <= N; i++) if (!comp[i]) for (int j = i * i; j <= N; j += i) comp[j] = 1;
    auto isP = [&](int x) { return x >= 2 && !comp[x]; };
    vector<int> b(n + 1);
    long long hi = n;
    while (hi >= 1) {
        int p = -1;  // smallest prime in (hi, 2*hi] (exists by Bertrand)
        for (long long c = hi + 1; c <= 2 * hi; c++) if (isP((int)c)) { p = (int)c; break; }
        for (long long i = p - hi; i <= hi; i++) b[i] = p - (int)i;  // i + b_i = p (prime)
        hi = p - hi - 1;
    }
    string out;
    for (int i = 1; i <= n; i++) { out += to_string(i); out += " \n"[i == n]; }
    for (int i = 1; i <= n; i++) { out += to_string(b[i]); out += " \n"[i == n]; }
    cout << out;
}
