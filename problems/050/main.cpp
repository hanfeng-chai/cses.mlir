#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<pair<long long, int>> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i].first; a[i].second = i + 1; }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        long long need = x - a[i].first;
        int lo = i + 1, hi = n - 1;
        while (lo < hi) {
            long long s = a[lo].first + a[hi].first;
            if (s == need) {
                cout << a[i].second << ' ' << a[lo].second << ' ' << a[hi].second << '\n';
                return 0;
            }
            if (s < need) lo++; else hi--;
        }
    }
    cout << "IMPOSSIBLE\n";
}
