#include <bits/stdc++.h>
using namespace std;
int main() {
    long long fact[21];
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) fact[i] = fact[i - 1] * i;
    int t; scanf("%d", &t);
    while (t--) {
        int type, n; scanf("%d %d", &type, &n);
        if (type == 1) {
            long long k; scanf("%lld", &k);
            k--;  // 0-indexed
            vector<int> avail; for (int i = 1; i <= n; i++) avail.push_back(i);
            for (int i = 0; i < n; i++) {
                long long idx = k / fact[n - 1 - i];
                k %= fact[n - 1 - i];
                printf("%d%c", avail[idx], " \n"[i == n - 1]);
                avail.erase(avail.begin() + idx);
            }
        } else {
            vector<int> p(n); for (auto &v : p) scanf("%d", &v);
            long long rank = 1;
            vector<int> avail; for (int i = 1; i <= n; i++) avail.push_back(i);
            for (int i = 0; i < n; i++) {
                int pos = lower_bound(avail.begin(), avail.end(), p[i]) - avail.begin();
                rank += (long long)pos * fact[n - 1 - i];
                avail.erase(avail.begin() + pos);
            }
            printf("%lld\n", rank);
        }
    }
}
