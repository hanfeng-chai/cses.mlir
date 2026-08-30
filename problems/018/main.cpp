#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;
        // 可行 <=> a+b<=n 且 a,b 同为 0 或同为正
        bool ok = (a + b <= n) && ((a == 0) == (b == 0));
        if (!ok) { cout << "NO\n"; continue; }
        cout << "YES\n";
        // 玩家2 出 1..n；玩家1 在前 a 位放大牌(赢)，再 b 位放小牌(输)，其余相等(平)
        vector<int> P(n + 1);
        if (a == 0) {
            for (int i = 1; i <= n; i++) P[i] = i;
        } else {
            for (int i = 1; i <= a; i++) P[i] = i + b;
            for (int i = a + 1; i <= a + b; i++) P[i] = i - a;
            for (int i = a + b + 1; i <= n; i++) P[i] = i;
        }
        for (int i = 1; i <= n; i++) cout << P[i] << " \n"[i == n];
        for (int i = 1; i <= n; i++) cout << i << " \n"[i == n];
    }
}
