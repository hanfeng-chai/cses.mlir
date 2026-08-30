#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG_INF = LLONG_MIN / 2;

// 383 Programmers and Artists.
// Exchange argument: in an optimal solution every programmer's (x_i-y_i) is >=
// every artist's (x_i-y_i) (otherwise swapping their roles improves the sum).
// So after sorting by (x_i-y_i) descending, all programmers occupy some prefix
// positions and all artists occupy some suffix positions, for SOME split point k
// (0<=k<=n): programmers are chosen as the top-`a`-by-x among the first k people,
// artists as the top-`b`-by-y among the last (n-k) people (people strictly
// between are simply not hired). Trying every k and taking the best is O(n log n)
// using a running min-heap of size a (resp. b) swept from the left (resp. right).
//
// NOTE: a naive "top a by (x-y) become programmers, the rest fight for artist
// among the immediately next b" is WRONG -- e.g. x=[100,1],y=[1,100],a=b=1: that
// greedy picks person1 as programmer (100) then person2 as artist (100) by luck,
// but with x=[100,1,1],y=[1,100,1] it would pick the "next by x-y" (the mediocre
// person, y=1) as artist instead of the true specialist (y=100) ranked last by
// x-y. Verified this split-point approach against that counterexample by hand.
int main() {
    ll a, b, n;
    scanf("%lld %lld %lld", &a, &b, &n);
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) scanf("%lld %lld", &x[i], &y[i]);

    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return x[i] - y[i] > x[j] - y[j];
    });

    vector<ll> bestP(n + 1, NEG_INF), bestA(n + 1, NEG_INF);
    {
        priority_queue<ll, vector<ll>, greater<ll>> heap; // min-heap, capped at size a
        ll sum = 0;
        bestP[0] = (a == 0) ? 0 : NEG_INF;
        for (ll k = 1; k <= n; k++) {
            ll v = x[idx[k - 1]];
            heap.push(v); sum += v;
            if ((ll)heap.size() > a) { sum -= heap.top(); heap.pop(); }
            bestP[k] = ((ll)heap.size() == a) ? sum : NEG_INF;
        }
    }
    {
        priority_queue<ll, vector<ll>, greater<ll>> heap; // min-heap, capped at size b
        ll sum = 0;
        bestA[n] = (b == 0) ? 0 : NEG_INF;
        for (ll k = n - 1; k >= 0; k--) {
            ll v = y[idx[k]];
            heap.push(v); sum += v;
            if ((ll)heap.size() > b) { sum -= heap.top(); heap.pop(); }
            bestA[k] = ((ll)heap.size() == b) ? sum : NEG_INF;
        }
    }

    ll best = 0;
    for (ll k = 0; k <= n; k++) {
        if (bestP[k] <= NEG_INF / 2 || bestA[k] <= NEG_INF / 2) continue;
        best = max(best, bestP[k] + bestA[k]);
    }
    printf("%lld\n", best);
}
