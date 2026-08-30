#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);  // (结束时间, 开始时间)
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v[i] = {b, a};
    }
    sort(v.begin(), v.end());     // 按结束时间贪心
    int cnt = 0;
    long long end = 0;
    for (auto &[b, a] : v)
        if (a >= end) { cnt++; end = b; }
    cout << cnt << '\n';
}
