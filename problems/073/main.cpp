#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    bitset<100001> dp;
    dp[0] = 1;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        tot += x;
        dp |= dp << x;
    }
    vector<int> sums;
    for (int s = 1; s <= tot; s++)
        if (dp[s]) sums.push_back(s);
    cout << sums.size() << "\n";
    for (size_t i = 0; i < sums.size(); i++)
        cout << sums[i] << " \n"[i + 1 == sums.size()];
    if (sums.empty()) cout << "\n";
}
