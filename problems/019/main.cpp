#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // 每格的 mex(左侧 + 上方) 恰好等于 i XOR j
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cout << (i ^ j) << " \n"[j == n - 1];
}
