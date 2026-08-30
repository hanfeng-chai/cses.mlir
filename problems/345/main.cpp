#include <bits/stdc++.h>
using namespace std;

namespace {
vector<int> permutation;
set<int> remaining;

bool finish_lexicographically(int previous) {
    if (remaining.empty()) return true;
    vector<int> candidates(remaining.begin(), remaining.end());
    for (int value : candidates) {
        if (abs(value - previous) == 1) continue;
        remaining.erase(value);
        permutation.push_back(value);
        if (finish_lexicographically(value)) return true;
        permutation.pop_back();
        remaining.insert(value);
    }
    return false;
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const vector<vector<int>> small = {
        {},
        {1},
        {},
        {},
        {2, 4, 1, 3},
        {1, 3, 5, 2, 4},
        {1, 3, 5, 2, 4, 6},
        {1, 3, 5, 2, 6, 4, 7},
        {1, 3, 5, 2, 6, 8, 4, 7},
        {1, 3, 5, 2, 4, 7, 9, 6, 8}
    };
    if (n <= 9) {
        if (small[n].empty()) {
            cout << "NO SOLUTION\n";
        } else {
            for (int value : small[n]) cout << value << ' ';
            cout << '\n';
        }
        return 0;
    }

    permutation = {1, 3, 5, 2, 4, 6, 8, 10};
    int odd_start = 7;
    int even_start = 12;
    bool odd_block = true;
    while ((int)permutation.size() + 15 < n) {
        int start = odd_block ? odd_start : even_start;
        for (int i = 0; i < 5; ++i) permutation.push_back(start + 2 * i);
        if (odd_block) odd_start += 10;
        else even_start += 10;
        odd_block = !odd_block;
    }

    vector<char> used(n + 1, false);
    for (int value : permutation) used[value] = true;
    for (int value = 1; value <= n; ++value) {
        if (!used[value]) remaining.insert(value);
    }
    bool completed = finish_lexicographically(permutation.back());
    if (!completed || (int)permutation.size() != n) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << permutation[i];
    }
    cout << '\n';
}
