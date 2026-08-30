#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (long long k = 1; k <= n; k++) {
        long long tot = k * k * (k * k - 1) / 2;          // 任取两格
        long long att = (k >= 2) ? 4 * (k - 1) * (k - 2) : 0;  // 互相攻击的对数
        cout << tot - att << '\n';
    }
}
