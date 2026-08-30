#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ll n, k; scanf("%lld %lld", &n, &k);
    int bas[31] = {0}, r = 0;
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x); int y = x;
        for (int b = 29; b >= 0; b--) if (y >> b & 1) { if (!bas[b]) { bas[b] = y; r++; break; } y ^= bas[b]; }
    }
    for (int b = 0; b < 30; b++) if (bas[b]) for (int c = b + 1; c < 30; c++) if (bas[c] && (bas[c] >> b & 1)) bas[c] ^= bas[b];  // RREF
    vector<int> lst;
    for (int b = 0; b < 30; b++) if (bas[b]) lst.push_back(bas[b]);  // ascending by leading bit
    ll nr = n - r; string out;
    if (nr >= 18) {  // each distinct value appears 2^(n-r) > k times, so all k smallest are 0
        for (ll i = 0; i < k; i++) { out += "0"; out += " \n"[i == k - 1]; }
    } else {
        ll m = 1LL << nr;
        for (ll p = 0; p < k; p++) {
            ll idx = p / m; int v = 0;
            for (int t = 0; t < (int)lst.size(); t++) if (idx >> t & 1) v ^= lst[t];
            out += to_string(v); out += " \n"[p == k - 1];
        }
    }
    cout << out;
}
