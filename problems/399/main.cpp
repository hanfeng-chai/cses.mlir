#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, limit;
    cin >> n >> limit;
    vector<int> skill(n);
    for (int &value : skill) cin >> value;
    sort(skill.begin(), skill.end());

    vector<vector<int>> dp(n + 1, vector<int>(limit + 1, 0));
    vector<vector<int>> next(n + 1, vector<int>(limit + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (vector<int> &row : next) fill(row.begin(), row.end(), 0);
        int gap = i == 0 ? 0 : skill[i] - skill[i - 1];

        for (int open = 0; open <= i; ++open) {
            int added_cost = open * gap;
            if (added_cost > limit) continue;
            for (int cost = 0; cost + added_cost <= limit; ++cost) {
                int ways = dp[open][cost];
                if (ways == 0) continue;
                int new_cost = cost + added_cost;

                next[open][new_cost] =
                    (next[open][new_cost] + 1LL * ways * (open + 1)) % MOD;
                next[open + 1][new_cost] += ways;
                if (next[open + 1][new_cost] >= MOD) next[open + 1][new_cost] -= MOD;
                if (open > 0) {
                    next[open - 1][new_cost] =
                        (next[open - 1][new_cost] + 1LL * ways * open) % MOD;
                }
            }
        }
        dp.swap(next);
    }

    int answer = 0;
    for (int cost = 0; cost <= limit; ++cost) {
        answer += dp[0][cost];
        if (answer >= MOD) answer -= MOD;
    }
    cout << answer << '\n';
}
