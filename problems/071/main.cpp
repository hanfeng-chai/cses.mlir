#include <bits/stdc++.h>
using namespace std;
int dp[501][501];
int main() {
    int a, b;
    cin >> a >> b;
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++) {
            if (i == j) { dp[i][j] = 0; continue; }
            int best = INT_MAX;
            for (int k = 1; k < i; k++) best = min(best, dp[k][j] + dp[i - k][j] + 1);
            for (int k = 1; k < j; k++) best = min(best, dp[i][k] + dp[i][j - k] + 1);
            dp[i][j] = best;
        }
    cout << dp[a][b] << "\n";
}
