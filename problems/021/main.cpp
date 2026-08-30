#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &r : g) cin >> r;
    vector<string> res = g;
    // 逐格贪心：选一个 != 原字符、且 != 左、!= 上 的字符（3 候选排除 <=2 个，必有解）
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (char c = 'A'; c <= 'D'; c++) {
                if (c == g[i][j]) continue;
                if (i > 0 && res[i - 1][j] == c) continue;
                if (j > 0 && res[i][j - 1] == c) continue;
                res[i][j] = c;
                break;
            }
    for (auto &r : res) cout << r << '\n';
}
