#include <bits/stdc++.h>
using namespace std;

namespace {
uint32_t cell_mask[500][500];
uint32_t column_mask[500];
uint32_t front_value[500], back_value[500];
uint32_t front_or[501], back_or[501];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    for (int y = 0; y < n; ++y) {
        string row;
        cin >> row;
        for (int x = 0; x < n; ++x) {
            cell_mask[y][x] = 1U << (row[x] - 'A');
        }
    }

    const uint32_t all_letters = (1U << k) - 1;
    long long answer = 0;
    for (int top = 0; top < n; ++top) {
        fill(column_mask, column_mask + n, 0U);
        for (int bottom = top; bottom < n; ++bottom) {
            uint32_t band_or = 0;
            for (int x = 0; x < n; ++x) {
                column_mask[x] |= cell_mask[bottom][x];
                band_or |= column_mask[x];
            }
            if (band_or != all_letters) continue;

            int front_size = 0, back_size = 0;
            front_or[0] = back_or[0] = 0;
            for (int right = 0; right < n; ++right) {
                back_value[back_size] = column_mask[right];
                back_or[back_size + 1] = back_or[back_size] | column_mask[right];
                ++back_size;

                while ((front_or[front_size] | back_or[back_size]) == all_letters) {
                    answer += n - right;
                    if (front_size == 0) {
                        while (back_size > 0) {
                            uint32_t value = back_value[--back_size];
                            front_value[front_size] = value;
                            front_or[front_size + 1] = front_or[front_size] | value;
                            ++front_size;
                        }
                        back_or[0] = 0;
                    }
                    --front_size;
                }
            }
        }
    }

    cout << answer << '\n';
}
