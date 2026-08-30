#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long rounds;
    cin >> n >> rounds;
    vector<int> values(n);
    for (int &value : values) cin >> value;

    int reach = min<long long>(n, rounds + 1);
    priority_queue<int, vector<int>, greater<int>> candidates;
    for (int i = 0; i < reach; ++i) candidates.push(values[i]);

    vector<int> result;
    result.reserve(n);
    for (int i = reach; i < n; ++i) {
        result.push_back(candidates.top());
        candidates.pop();
        candidates.push(values[i]);
    }
    while (!candidates.empty()) {
        result.push_back(candidates.top());
        candidates.pop();
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << result[i];
    }
    cout << '\n';
}
