#include <bits/stdc++.h>
using namespace std;

// 391 Book Shop II: bounded knapsack (k_i limited copies of each book).
// Split each book's k_i copies into O(log k_i) groups by binary decomposition
// (1,2,4,...,remainder copies), turning each group into a single 0/1 item, then
// run standard 0/1 knapsack. Total items ~ n*log(maxK), well within limits.
int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    vector<int> h(n), s(n), k(n);
    for (auto &v : h) scanf("%d", &v);
    for (auto &v : s) scanf("%d", &v);
    for (auto &v : k) scanf("%d", &v);

    vector<pair<int,int>> items; // (price, pages) per binary-split group
    for (int i = 0; i < n; i++) {
        int rem = k[i];
        for (int take = 1; rem > 0; take *= 2) {
            int cnt = min(take, rem);
            items.push_back({h[i] * cnt, s[i] * cnt});
            rem -= cnt;
        }
    }

    vector<int> dp(x + 1, 0);
    for (auto &it : items) {
        int price = it.first, pages = it.second;
        for (int c = x; c >= price; c--)
            dp[c] = max(dp[c], dp[c - price] + pages);
    }
    printf("%d\n", dp[x]);
}
