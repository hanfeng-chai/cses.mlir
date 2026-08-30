#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, n;
    cin >> x >> n;
    set<int> pts = {0, x};       // 已有灯的位置（含两端）
    multiset<int> seg = {x};     // 各段长度
    string out;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        auto it = pts.lower_bound(p);  // p 互异，这是第一个 > p 的灯
        int hi = *it, lo = *prev(it);
        seg.erase(seg.find(hi - lo));  // 旧段被 p 分成两段
        seg.insert(p - lo);
        seg.insert(hi - p);
        pts.insert(p);
        out += to_string(*seg.rbegin());
        out += (i + 1 < n ? ' ' : '\n');
    }
    cout << out;
}
