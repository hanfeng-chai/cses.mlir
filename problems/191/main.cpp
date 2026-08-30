#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> p(k);
    for (auto &v : p) scanf("%d", &v);
    string res(n + 1, 'L');
    vector<char> win(n + 1, 0);  // win[0] = lose (no move)
    for (int i = 1; i <= n; i++) {
        for (int x : p) if (x <= i && !win[i - x]) { win[i] = 1; break; }
        res[i] = win[i] ? 'W' : 'L';
    }
    printf("%s\n", res.c_str() + 1);
}
