#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> arr, pos;

// 断点：value v 出现在 v-1 之前则贡献 1（v 在 [2,n]）
int contrib(int v) { return (v >= 2 && v <= n && pos[v] < pos[v - 1]) ? 1 : 0; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    arr.assign(n + 1, 0);
    pos.assign(n + 2, 0);
    for (int i = 1; i <= n; i++) { cin >> arr[i]; pos[arr[i]] = i; }
    int cnt = 0;  // 断点总数；rounds = cnt + 1
    for (int v = 2; v <= n; v++) cnt += contrib(v);
    string out;
    while (m--) {
        int a, b;
        cin >> a >> b;
        int va = arr[a], vb = arr[b];
        // 只有这几个断点会受 pos[va]/pos[vb] 变化影响
        int idx[] = {va, va + 1, vb, vb + 1};
        set<int> uniq(idx, idx + 4);
        for (int w : uniq) cnt -= contrib(w);
        swap(arr[a], arr[b]);
        pos[va] = b; pos[vb] = a;
        for (int w : uniq) cnt += contrib(w);
        out += to_string(cnt + 1);
        out += '\n';
    }
    cout << out;
}
