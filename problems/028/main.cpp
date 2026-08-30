#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    multiset<int> s;
    for (int i = 0; i < n; i++) { int h; cin >> h; s.insert(h); }
    while (m--) {
        int t;
        cin >> t;
        auto it = s.upper_bound(t);   // 第一个 > t 的票
        if (it == s.begin()) { cout << -1 << '\n'; continue; }
        --it;                         // 退一格 = 不超过 t 的最大票
        cout << *it << '\n';
        s.erase(it);
    }
}
