#include <bits/stdc++.h>
using namespace std;

// 387 Grid Puzzle I: existence + construction of a 0/1 n x n matrix with given
// row sums a_i and column sums b_j (Gale-Ryser realizability). Standard greedy
// construction: process rows in decreasing order of remaining a_i; for each row,
// place its 1s in the a_i columns that currently have the largest remaining b_j.
int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n), b(n);
    for (auto &v : a) scanf("%d", &v);
    for (auto &v : b) scanf("%d", &v);

    vector<int> rowOrder(n);
    for (int i = 0; i < n; i++) rowOrder[i] = i;
    sort(rowOrder.begin(), rowOrder.end(), [&](int i, int j) { return a[i] > a[j]; });

    vector<string> grid(n, string(n, '.'));
    priority_queue<pair<int,int>> pq; // (remaining b_j, column index)
    for (int j = 0; j < n; j++) pq.push({b[j], j});

    bool ok = true;
    for (int r : rowOrder) {
        int need = a[r];
        if (need == 0) continue;
        vector<pair<int,int>> popped;
        for (int k = 0; k < need; k++) {
            if (pq.empty() || pq.top().first == 0) { ok = false; break; }
            popped.push_back(pq.top());
            pq.pop();
        }
        if (!ok) break;
        for (auto &pr : popped) {
            grid[r][pr.second] = 'X';
            pq.push({pr.first - 1, pr.second});
        }
    }
    if (ok) {
        // defensive check: all column sums must now be exhausted
        while (!pq.empty()) {
            if (pq.top().first != 0) { ok = false; break; }
            pq.pop();
        }
    }

    if (!ok) {
        printf("-1\n");
        return 0;
    }
    for (auto &row : grid) printf("%s\n", row.c_str());
}
