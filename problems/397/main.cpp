#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 397 Stick Divisions: splitting is the reverse of merging, and the total split
// cost equals the sum over all internal nodes of a binary merge-tree whose leaves
// are the target lengths. Minimizing that sum is exactly the classic Huffman
// algorithm: repeatedly merge the two smallest current values.
int main() {
    ll x; int n;
    scanf("%lld %d", &x, &n);
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 0; i < n; i++) { ll d; scanf("%lld", &d); pq.push(d); }

    ll total = 0;
    while (pq.size() > 1) {
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();
        ll merged = a + b;
        total += merged;
        pq.push(merged);
    }
    printf("%lld\n", total);
}
