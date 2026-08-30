#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) { int x; cin >> x; pos[x] = i; }
    int rounds = 1;
    // 每当 value v 出现在 v-1 之前，就必须多开一轮
    for (int v = 2; v <= n; v++)
        if (pos[v] < pos[v - 1]) rounds++;
    cout << rounds << '\n';
}
