#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<pair<long long, int>> a(n);  // (值, 原始下标 1-based)
    for (int i = 0; i < n; i++) { cin >> a[i].first; a[i].second = i + 1; }
    sort(a.begin(), a.end());
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        long long s = a[lo].first + a[hi].first;
        if (s == x) { cout << a[lo].second << ' ' << a[hi].second << '\n'; return 0; }
        if (s < x) lo++; else hi--;
    }
    cout << "IMPOSSIBLE\n";
}
