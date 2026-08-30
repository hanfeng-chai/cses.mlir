#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    long long S = 0;
    for (auto &v : a) { cin >> v; S += v; }
    // f[i] holds dp for the current interval length; we grow length in place.
    // dp[i][j] = best score difference (current player - opponent) on a[i..j]
    vector<long long> f(a.begin(), a.end());
    for (int len = 1; len < n; len++)
        for (int i = 0; i + len < n; i++)
            f[i] = max(a[i] - f[i + 1], a[i + len] - f[i]);
    long long diff = f[0];
    cout << (S + diff) / 2 << "\n";
}
