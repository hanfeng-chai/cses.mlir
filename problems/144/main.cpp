#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> ch(n + 1);
    for (int i = 2; i <= n; i++) { int b; scanf("%d", &b); ch[b].push_back(i); }
    vector<int> order; order.reserve(n);
    vector<int> st = {1};
    while (!st.empty()) { int u = st.back(); st.pop_back(); order.push_back(u); for (int v : ch[u]) st.push_back(v); }
    vector<int> sz(n + 1, 1);
    for (int i = (int)order.size() - 1; i >= 0; i--) { int u = order[i]; for (int v : ch[u]) sz[u] += sz[v]; }
    for (int i = 1; i <= n; i++) printf("%d%c", sz[i] - 1, " \n"[i == n]);
}
