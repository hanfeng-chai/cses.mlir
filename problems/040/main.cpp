#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &v : x) cin >> v;
    unordered_map<int, int> last;  // 值最近出现位置
    last.reserve(2 * n);
    long long ans = 0;
    int l = 0;
    // 对每个右端 r，最小合法左端 l；贡献以 r 结尾的 r-l+1 个子数组
    for (int r = 0; r < n; r++) {
        auto it = last.find(x[r]);
        if (it != last.end() && it->second >= l) l = it->second + 1;
        last[x[r]] = r;
        ans += r - l + 1;
    }
    cout << ans << '\n';
}
