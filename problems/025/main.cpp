#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v : a) cin >> v;
    sort(a.begin(), a.end());
    cout << (unique(a.begin(), a.end()) - a.begin()) << '\n';  // 去重后剩余个数
}
