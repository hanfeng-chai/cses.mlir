#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long total = 0, mx = 0;
    for (int i = 0; i < n; i++) { long long t; cin >> t; total += t; mx = max(mx, t); }
    // 最长一本书 > 其余总和时受其限制，否则可完全错峰
    cout << max(total, 2 * mx) << '\n';
}
