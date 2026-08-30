#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &v : p) cin >> v;
    sort(p.begin(), p.end());
    long long med = p[n / 2], cost = 0;  // 中位数最优
    for (int v : p) cost += llabs((long long)v - med);
    cout << cost << '\n';
}
