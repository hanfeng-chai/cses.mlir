#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 385 Coin Arrangement: 2xn grid, want exactly 1 coin per cell, minimize total
// unit moves. Modeled as choosing vertical transfers v_i (row1->row2 at column i)
// then solving the two independent 1-D "equalize via adjacent moves" problems for
// the two rows. The DP over the running row-1 prefix P1_i is a convex piecewise
// linear function of the state, handled with slope trick:
//   - transitioning to the next column shifts the domain by (a_i-1), then
//     convolves with |.| (which clips the slopes to magnitude <= 1, i.e. keep
//     only the closest breakpoint on each side of the flat minimum),
//   - then two V-shapes |p-0| and |p-C_i| are added, where C_i is the cumulative
//     sum of (a_j+b_j-2) up to column i (this is P1_i+P2_i, a fixed quantity).
// Final answer = value of the resulting function at p=0 (P1_n must be 0).
int main() {
    int n;
    scanf("%d", &n);
    vector<ll> a(n), b(n);
    for (auto &v : a) scanf("%lld", &v);
    for (auto &v : b) scanf("%lld", &v);

    vector<ll> L, R; // small (<=3 elements) slope-trick breakpoint lists
    ll minval = 0;

    auto addAbs = [&](ll c) {
        L.push_back(c);
        R.push_back(c);
        int li = 0;
        for (int i = 1; i < (int)L.size(); i++) if (L[i] > L[li]) li = i;
        int ri = 0;
        for (int i = 1; i < (int)R.size(); i++) if (R[i] < R[ri]) ri = i;
        ll l = L[li], r = R[ri];
        if (l > r) {
            L.erase(L.begin() + li);
            R.erase(R.begin() + ri);
            minval += l - r;
            L.push_back(r);
            R.push_back(l);
        }
    };
    auto shiftBy = [&](ll delta) {
        for (auto &x : L) x += delta;
        for (auto &x : R) x += delta;
    };
    auto clip = [&]() {
        if (!L.empty()) { ll mx = *max_element(L.begin(), L.end()); L.assign(1, mx); }
        if (!R.empty()) { ll mn = *min_element(R.begin(), R.end()); R.assign(1, mn); }
    };
    auto evalAt = [&](ll p) -> ll {
        ll cost = minval;
        for (ll l : L) if (l > p) cost += l - p;
        for (ll r : R) if (r < p) cost += p - r;
        return cost;
    };

    L = {a[0] - 1};
    R = {a[0] - 1};
    if (n == 1) {
        printf("%lld\n", evalAt(0));
        return 0;
    }

    ll runC = a[0] + b[0] - 2;
    addAbs(0);
    addAbs(runC);
    for (int i = 1; i < n - 1; i++) {
        shiftBy(a[i] - 1);
        clip();
        addAbs(0);
        runC += a[i] + b[i] - 2;
        addAbs(runC);
    }
    shiftBy(a[n - 1] - 1);
    clip();
    printf("%lld\n", evalAt(0));
}
