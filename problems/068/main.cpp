#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
const int MX = 1e6 + 1;
int main() {
    vector<long long> ans(MX);
    long long a = 1, b = 1;  // height 1: a=split(two 1x1), b=merged(one 1x2)
    ans[1] = 2;
    for (int i = 2; i < MX; i++) {
        long long na = (4 * a + b) % MOD, nb = (a + 2 * b) % MOD;
        a = na; b = nb;
        ans[i] = (a + b) % MOD;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << ans[n] << "\n";
    }
}
