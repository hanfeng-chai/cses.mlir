#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> A(n);
    for (auto &v : A) cin >> v;
    // 枚举第二对 (i,k)，在 map 中找下标更小的第一对，保证四个下标互异
    unordered_map<long long, pair<int, int>> m;
    m.reserve(2 * n * n);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i - 1; j++)
            m.emplace(A[j] + A[i - 1], make_pair(j, i - 1));
        for (int k = i + 1; k < n; k++) {
            auto it = m.find(x - A[i] - A[k]);
            if (it != m.end()) {
                auto [c, d] = it->second;
                cout << c + 1 << ' ' << d + 1 << ' ' << i + 1 << ' ' << k + 1 << '\n';
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
