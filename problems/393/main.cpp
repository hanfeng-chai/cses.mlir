#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> values(n);
    for (long long &value : values) cin >> value;
    sort(values.begin(), values.end());

    constexpr long long INF = 1LL << 60;
    vector<long long> weight(n + 1, INF);
    vector<int> left(n + 1), right(n + 1);
    vector<char> removed(n + 1, false);
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> queue;

    left[0] = 0;
    right[0] = 1;
    left[n] = n - 1;
    right[n] = n;
    for (int edge = 1; edge < n; ++edge) {
        weight[edge] = values[edge] - values[edge - 1];
        left[edge] = edge - 1;
        right[edge] = edge + 1;
        queue.push({weight[edge], edge});
    }

    long long total = 0;
    for (int pairs = 1; pairs <= n / 2; ++pairs) {
        while (removed[queue.top().second]) queue.pop();
        auto [increment, edge] = queue.top();
        queue.pop();
        total += increment;
        if (pairs > 1) cout << ' ';
        cout << total;

        int previous = left[edge];
        int next = right[edge];
        weight[edge] = min(INF, weight[previous] + weight[next] - weight[edge]);
        removed[previous] = true;
        removed[next] = true;

        left[edge] = left[previous];
        right[edge] = right[next];
        right[left[edge]] = edge;
        left[right[edge]] = edge;
        queue.push({weight[edge], edge});
    }
    cout << '\n';
}
