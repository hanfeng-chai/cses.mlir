#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M1 = 1e9 + 7, M2 = 998244353, B = 131;
ll pe(ll a, ll b, ll m) { ll r = 1; a %= m; while (b) { if (b & 1) r = r * a % m; a = a * a % m; b >>= 1; } return r; }
struct BIT {
    int n; vector<ll> t; ll mod;
    void init(int n_, ll m_) { n = n_; mod = m_; t.assign(n + 1, 0); }
    void add(int i, ll v) { for (i++; i <= n; i += i & -i) t[i] = (t[i] + v) % mod; }
    ll sum(int i) { ll s = 0; for (i++; i > 0; i -= i & -i) s = (s + t[i]) % mod; return s; }
    ll range(int l, int r) { return ((sum(r) - sum(l - 1)) % mod + mod) % mod; }
};
BIT F1, F2, R1, R2;
ll pw1[200005], ipw1[200005], pw2[200005], ipw2[200005];
int n, m;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m; string s; cin >> s;
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < n; i++) { pw1[i] = pw1[i - 1] * B % M1; pw2[i] = pw2[i - 1] * B % M2; }
    ll iB1 = pe(B, M1 - 2, M1), iB2 = pe(B, M2 - 2, M2);
    ipw1[0] = ipw2[0] = 1;
    for (int i = 1; i < n; i++) { ipw1[i] = ipw1[i - 1] * iB1 % M1; ipw2[i] = ipw2[i - 1] * iB2 % M2; }
    F1.init(n, M1); F2.init(n, M2); R1.init(n, M1); R2.init(n, M2);
    vector<int> val(n);
    for (int i = 0; i < n; i++) {  // forward weights p^i, reverse weights p^(n-1-i)
        val[i] = s[i] - 'a' + 1;
        F1.add(i, (ll)val[i] * pw1[i] % M1); F2.add(i, (ll)val[i] * pw2[i] % M2);
        R1.add(i, (ll)val[i] * pw1[n - 1 - i] % M1); R2.add(i, (ll)val[i] * pw2[n - 1 - i] % M2);
    }
    while (m--) {
        int type; cin >> type;
        if (type == 1) {
            int k; char x; cin >> k >> x; k--; int nv = x - 'a' + 1, d = nv - val[k];
            if (d) {
                F1.add(k, ((ll)d * pw1[k] % M1 + M1) % M1); F2.add(k, ((ll)d * pw2[k] % M2 + M2) % M2);
                R1.add(k, ((ll)d * pw1[n - 1 - k] % M1 + M1) % M1); R2.add(k, ((ll)d * pw2[n - 1 - k] % M2 + M2) % M2);
                val[k] = nv;
            }
        } else {
            int a, b; cin >> a >> b; a--; b--;
            ll f1 = F1.range(a, b) * ipw1[a] % M1, f2 = F2.range(a, b) * ipw2[a] % M2;
            ll r1 = R1.range(a, b) * ipw1[n - 1 - b] % M1, r2 = R2.range(a, b) * ipw2[n - 1 - b] % M2;
            cout << ((f1 == r1 && f2 == r2) ? "YES" : "NO") << "\n";
        }
    }
}
