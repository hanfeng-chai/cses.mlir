#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> forest(n);
    for (string &row : forest) cin >> row;

    int stride = m + 3;
    vector<long long> second_difference((n + 2) * stride, 0);
    vector<int> height(m, 0), left(m), right(m), stack;
    stack.reserve(m);

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            height[x] = forest[y][x] == '*' ? 0 : height[x] + 1;
        }

        stack.clear();
        for (int x = 0; x < m; ++x) {
            while (!stack.empty() && height[stack.back()] >= height[x]) stack.pop_back();
            left[x] = stack.empty() ? 0 : stack.back() + 1;
            stack.push_back(x);
        }
        stack.clear();
        for (int x = m - 1; x >= 0; --x) {
            while (!stack.empty() && height[stack.back()] > height[x]) stack.pop_back();
            right[x] = stack.empty() ? m - 1 : stack.back() - 1;
            stack.push_back(x);
        }

        for (int x = 0; x < m; ++x) {
            int h = height[x];
            if (h == 0) continue;
            int a = x - left[x] + 1;
            int b = right[x] - x + 1;
            if (a > b) swap(a, b);
            long long *difference = &second_difference[h * stride];
            ++difference[1];
            --difference[a + 1];
            --difference[b + 1];
            ++difference[a + b + 1];
        }
    }

    vector<long long> answer((n + 2) * stride, 0);
    for (int h = 1; h <= n; ++h) {
        long long slope = 0, value = 0;
        for (int w = 1; w <= m; ++w) {
            slope += second_difference[h * stride + w];
            value += slope;
            answer[h * stride + w] = value;
        }
    }
    for (int w = 1; w <= m; ++w) {
        for (int h = n - 1; h >= 1; --h) {
            answer[h * stride + w] += answer[(h + 1) * stride + w];
        }
    }

    for (int h = 1; h <= n; ++h) {
        for (int w = 1; w <= m; ++w) {
            if (w > 1) cout << ' ';
            cout << answer[h * stride + w];
        }
        cout << '\n';
    }
}
