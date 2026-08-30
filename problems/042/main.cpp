#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    queue<int> q;
    for (int i = 1; i <= n; i++) q.push(i);
    string out;
    while (!q.empty()) {
        q.push(q.front()); q.pop();      // 跳过一个
        out += to_string(q.front());     // 移除下一个
        out += ' ';
        q.pop();
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
}
