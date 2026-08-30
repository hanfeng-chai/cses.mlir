#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    multiset<int> tops;  // 各塔顶的大小
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        auto it = tops.upper_bound(c);  // 第一个严格大于 c 的塔顶
        if (it == tops.end()) tops.insert(c);          // 没有可放之塔 -> 新建
        else { tops.erase(it); tops.insert(c); }       // 放上去，塔顶变为 c
    }
    cout << tops.size() << '\n';
}
