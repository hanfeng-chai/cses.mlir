#include <bits/stdc++.h>
using namespace std;

string out;

// 把 n 个盘从 from 经 via 移到 to，标准递归即最优解
void hanoi(int n, int from, int to, int via) {
    if (n == 0) return;
    hanoi(n - 1, from, via, to);
    out += to_string(from) + " " + to_string(to) + "\n";
    hanoi(n - 1, via, to, from);
}

int main() {
    int n;
    cin >> n;
    cout << ((1 << n) - 1) << '\n';
    hanoi(n, 1, 3, 2);
    cout << out;
}
