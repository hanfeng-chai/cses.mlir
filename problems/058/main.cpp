#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> v(n);  // (结束, 开始)
    for (int i = 0; i < n; i++) { int a, b; cin >> a >> b; v[i] = {b, a}; }
    sort(v.begin(), v.end());     // 按结束时间
    multiset<int> ms;             // k 个成员各自上次看完的时间
    for (int i = 0; i < k; i++) ms.insert(0);
    int cnt = 0;
    for (auto &[b, a] : v) {
        auto it = ms.upper_bound(a);  // 第一个 > a
        if (it == ms.begin()) continue;  // 没有空闲时间 <= a 的成员
        --it;                            // 取 <= a 的最大者（最迟空闲的）
        ms.erase(it);
        ms.insert(b);
        cnt++;
    }
    cout << cnt << '\n';
}
