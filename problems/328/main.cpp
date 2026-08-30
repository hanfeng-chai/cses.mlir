#include <bits/stdc++.h>
using namespace std;

namespace {
uint16_t upward_run[500][500];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<string> grid(n);
    for (string &row : grid) cin >> row;

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (y > 0 && grid[y][x] == grid[y - 1][x]) {
                upward_run[y][x] = upward_run[y - 1][x] + 1;
            } else {
                upward_run[y][x] = 1;
            }
        }
    }

    vector<long long> answer(k, 0);
    for (int top = 0; top < n; ++top) {
        for (int bottom = top; bottom < n; ++bottom) {
            int height = bottom - top + 1;
            int active_letter = -1;
            int valid_left_borders = 0;
            for (int x = 0; x < n; ++x) {
                int letter = grid[top][x] == grid[bottom][x]
                                 ? grid[top][x] - 'A'
                                 : -1;
                if (letter != active_letter) {
                    active_letter = letter;
                    valid_left_borders = 0;
                }
                if (letter != -1 && upward_run[bottom][x] >= height) {
                    answer[letter] += valid_left_borders + 1;
                    ++valid_left_borders;
                }
            }
        }
    }

    for (long long value : answer) cout << value << '\n';
}
