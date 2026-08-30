#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> k(n);
    for (auto &v : k) cin >> v;
    unordered_map<int, int> last;  // 每个 id 最近出现的位置
    last.reserve(2 * n);
    int l = 0, best = 0;
    for (int r = 0; r < n; r++) {
        auto it = last.find(k[r]);
        if (it != last.end() && it->second >= l) l = it->second + 1;  // 收缩左端
        last[k[r]] = r;
        best = max(best, r - l + 1);
    }
    cout << best << '\n';
}
