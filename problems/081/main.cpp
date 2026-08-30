#include <bits/stdc++.h>
using namespace std;
string Sd;
long long memo[19][11][2][2];
bool vis[19][11][2][2];
// count integers in [0, Sd] with no two adjacent equal digits
long long dp(int pos, int prev, int tight, int started) {
    if (pos == (int)Sd.size()) return 1;
    if (vis[pos][prev][tight][started]) return memo[pos][prev][tight][started];
    vis[pos][prev][tight][started] = 1;
    int hi = tight ? Sd[pos] - '0' : 9;
    long long res = 0;
    for (int d = 0; d <= hi; d++) {
        int nt = tight && (d == hi);
        if (!started) {
            if (d == 0) res += dp(pos + 1, 10, nt, 0);   // leading zero, not started yet
            else res += dp(pos + 1, d, nt, 1);
        } else {
            if (d == prev) continue;
            res += dp(pos + 1, d, nt, 1);
        }
    }
    return memo[pos][prev][tight][started] = res;
}
long long f(long long x) {
    if (x < 0) return 0;
    Sd = to_string(x);
    memset(vis, 0, sizeof(vis));
    return dp(0, 10, 1, 0);
}
int main() {
    long long a, b;
    cin >> a >> b;
    cout << f(b) - f(a - 1) << "\n";
}
