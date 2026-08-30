#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int n; scanf("%d", &n);
    vector<pair<ll, ll>> p(n);
    for (auto &pp : p) scanf("%lld %lld", &pp.first, &pp.second);
    sort(p.begin(), p.end());
    ll best = LLONG_MAX;
    set<pair<ll, ll>> st;  // active points keyed by (y, x)
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < i && (p[i].first - p[j].first) * (p[i].first - p[j].first) > best) { st.erase({p[j].second, p[j].first}); j++; }
        ll d = (ll)sqrtl((long double)best) + 1;
        auto lo = st.lower_bound({p[i].second - d, LLONG_MIN});
        auto hi = st.upper_bound({p[i].second + d, LLONG_MAX});
        for (auto it = lo; it != hi; ++it) {
            ll dx = p[i].first - it->second, dy = p[i].second - it->first;
            best = min(best, dx * dx + dy * dy);
        }
        st.insert({p[i].second, p[i].first});
    }
    printf("%lld\n", best);
}
