#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> e;
    e.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        e.push_back({a, 1});   // 到达 +1
        e.push_back({b, -1});  // 离开 -1
    }
    sort(e.begin(), e.end());  // 同刻离开(-1)排在到达(+1)前；题目保证时刻互异
    int cur = 0, best = 0;
    for (auto &[t, d] : e) { cur += d; best = max(best, cur); }
    cout << best << '\n';
}
