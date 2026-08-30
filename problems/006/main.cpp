#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long y, x;
        cin >> y >> x;
        long long m = max(y, x), base = (m - 1) * (m - 1), v;
        if (m % 2 == 0) v = (x == m) ? base + y : base + 2 * m - x;
        else            v = (y == m) ? base + x : base + 2 * m - y;
        cout << v << '\n';
    }
}
