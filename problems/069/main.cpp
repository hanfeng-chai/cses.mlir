#include <bits/stdc++.h>
using namespace std;
int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    vector<int> prev(m + 1), cur(m + 1);
    for (int j = 0; j <= m; j++) prev[j] = j;
    for (int i = 1; i <= n; i++) {
        cur[0] = i;
        for (int j = 1; j <= m; j++) {
            int c = (a[i - 1] == b[j - 1]) ? 0 : 1;
            cur[j] = min({prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + c});
        }
        swap(prev, cur);
    }
    cout << prev[m] << "\n";
}
