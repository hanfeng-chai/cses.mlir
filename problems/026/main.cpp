#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<long long> a(n), b(m);
    for (auto &v : a) cin >> v;
    for (auto &v : b) cin >> v;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i = 0, j = 0, cnt = 0;
    // 双指针贪心：申请人与公寓都升序，能配则配
    while (i < n && j < m) {
        if (llabs(a[i] - b[j]) <= k) { cnt++; i++; j++; }
        else if (a[i] + k < b[j]) i++;   // 此申请人接受上限仍小于当前公寓 -> 配不上
        else j++;                        // 公寓太小 -> 换更大的
    }
    cout << cnt << '\n';
}
