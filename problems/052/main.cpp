#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    stack<pair<int, int>> st;  // (值, 下标)，单调递增栈
    string out;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (!st.empty() && st.top().first >= x) st.pop();
        out += to_string(st.empty() ? 0 : st.top().second);
        out += (i < n ? ' ' : '\n');
        st.push({x, i});
    }
    cout << out;
}
