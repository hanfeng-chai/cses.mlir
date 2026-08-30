#include <bits/stdc++.h>
using namespace std;

namespace {
constexpr int MAX_N = 3000;
uint16_t top_left_reach[MAX_N * MAX_N];
uint16_t bottom_right_reach[MAX_N * MAX_N];
uint8_t color[MAX_N * MAX_N];
int16_t fenwick[26][MAX_N + 1];
int expire_head[MAX_N + 1];
int expire_next[MAX_N];
int diagonal_offset[2 * MAX_N];

void add(int letter, int position, int delta, int length) {
    for (int p = position; p <= length; p += p & -p) {
        fenwick[letter][p] += delta;
    }
}

int prefix_sum(int letter, int position) {
    int result = 0;
    for (int p = position; p > 0; p -= p & -p) {
        result += fenwick[letter][p];
    }
    return result;
}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<string> grid(n);
    for (string &row : grid) cin >> row;

    diagonal_offset[0] = 0;
    for (int diagonal = 0; diagonal < 2 * n - 1; ++diagonal) {
        int length = diagonal < n ? diagonal + 1 : 2 * n - 1 - diagonal;
        diagonal_offset[diagonal + 1] = diagonal_offset[diagonal] + length;
    }

    vector<uint16_t> vertical(n, 0);
    vector<long long> answer(k, 0);
    for (int y = 0; y < n; ++y) {
        uint16_t horizontal = 0;
        for (int x = 0; x < n; ++x) {
            if (x > 0 && grid[y][x] == grid[y][x - 1]) ++horizontal;
            else horizontal = 1;
            if (y > 0 && grid[y][x] == grid[y - 1][x]) ++vertical[x];
            else vertical[x] = 1;
            int diagonal = y - x + n - 1;
            int position = diagonal_offset[diagonal] + min(y, x);
            top_left_reach[position] = min(horizontal, vertical[x]);
            color[position] = grid[y][x] - 'A';
            ++answer[color[position]];
        }
    }

    fill(vertical.begin(), vertical.end(), 0);
    for (int y = n - 1; y >= 0; --y) {
        uint16_t horizontal = 0;
        for (int x = n - 1; x >= 0; --x) {
            if (x + 1 < n && grid[y][x] == grid[y][x + 1]) ++horizontal;
            else horizontal = 1;
            if (y + 1 < n && grid[y][x] == grid[y + 1][x]) ++vertical[x];
            else vertical[x] = 1;
            int diagonal = y - x + n - 1;
            int position = diagonal_offset[diagonal] + min(y, x);
            bottom_right_reach[position] = min(horizontal, vertical[x]);
        }
    }

    auto process_diagonal = [&](int diagonal) {
        int begin = diagonal_offset[diagonal];
        int length = diagonal_offset[diagonal + 1] - begin;
        fill(expire_head, expire_head + length + 1, -1);

        for (int i = 0; i < length; ++i) {
            int reach = bottom_right_reach[begin + i];
            if (reach >= 2 && i + reach < length) {
                expire_next[i] = expire_head[i + reach];
                expire_head[i + reach] = i;
            }
        }

        for (int j = 0; j < length; ++j) {
            for (int i = expire_head[j]; i != -1; i = expire_next[i]) {
                add(color[begin + i], i + 1, -1, length);
            }

            int letter = color[begin + j];
            if (bottom_right_reach[begin + j] >= 2) {
                add(letter, j + 1, 1, length);
            }

            int reach = top_left_reach[begin + j];
            if (reach >= 2) {
                int minimum_top_left = max(0, j - reach + 1);
                answer[letter] += prefix_sum(letter, j) -
                                  prefix_sum(letter, minimum_top_left);
            }
        }

        for (int i = 0; i < length; ++i) {
            int reach = bottom_right_reach[begin + i];
            if (reach >= 2 && i + reach >= length) {
                add(color[begin + i], i + 1, -1, length);
            }
        }
    };

    for (int diagonal = 0; diagonal < 2 * n - 1; ++diagonal) {
        process_diagonal(diagonal);
    }

    for (long long value : answer) cout << value << '\n';
}
