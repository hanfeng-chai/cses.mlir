#include <bits/stdc++.h>
using namespace std;

namespace {
char grid[3000][3001];
uint16_t nearest_below[3000][26];
uint16_t need[2][3001][26];
uint16_t nearest_right[26];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    for (int y = 0; y < n; ++y) cin >> grid[y];

    for (int x = 0; x < n; ++x)
        for (int letter = 0; letter < k; ++letter)
            nearest_below[x][letter] = n;
    for (int parity = 0; parity < 2; ++parity)
        for (int x = 0; x <= n; ++x)
            for (int letter = 0; letter < k; ++letter)
                need[parity][x][letter] = n + 1;

    long long answer = 0;
    for (int y = n - 1; y >= 0; --y) {
        int current = y & 1;
        int inner = current ^ 1;
        for (int x = 0; x < n; ++x) {
            nearest_below[x][grid[y][x] - 'A'] = y;
        }
        fill(nearest_right, nearest_right + k, (uint16_t)n);

        for (int x = n - 1; x >= 0; --x) {
            nearest_right[grid[y][x] - 'A'] = x;
            int minimum_side = 0;
            for (int letter = 0; letter < k; ++letter) {
                int from_top = nearest_right[letter] - x + 1;
                int from_left = nearest_below[x][letter] - y + 1;
                int from_inner = need[inner][x + 1][letter] + 1;
                int side = min({from_top, from_left, from_inner});
                need[current][x][letter] = side;
                minimum_side = max(minimum_side, side);
            }
            int maximum_side = min(n - y, n - x);
            if (minimum_side <= maximum_side) {
                answer += maximum_side - minimum_side + 1;
            }
        }
    }

    cout << answer << '\n';
}
