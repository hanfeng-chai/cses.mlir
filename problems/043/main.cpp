#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> bit;
void upd(int i, int v) { for (; i <= N; i += i & -i) bit[i] += v; }
// 找第 j 个仍存在的孩子（1-indexed 顺序）
int findk(int j) {
    int idx = 0;
    for (int pw = 1 << 18; pw; pw >>= 1)
        if (idx + pw <= N && bit[idx + pw] < j) { idx += pw; j -= bit[idx]; }
    return idx + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k;
    cin >> n >> k;
    N = n;
    bit.assign(N + 1, 0);
    for (int i = 1; i <= N; i++) upd(i, 1);
    long long remaining = n, pos = 0;
    string out;
    for (int t = 0; t < n; t++) {
        pos = (pos + k) % remaining;          // 跳过 k 个后的 0-based 位置
        int c = findk((int)pos + 1);
        out += to_string(c);
        out += (t + 1 < n ? ' ' : '\n');
        upd(c, -1);
        remaining--;
    }
    cout << out;
}
