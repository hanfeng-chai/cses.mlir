#include <bits/stdc++.h>
using namespace std;

vector<string> board(8);
bool col[8] = {}, diag1[15] = {}, diag2[15] = {};
int cnt = 0;

void solve(int r) {
    if (r == 8) { cnt++; return; }
    for (int c = 0; c < 8; c++) {
        if (board[r][c] == '*' || col[c] || diag1[r + c] || diag2[r - c + 7]) continue;
        col[c] = diag1[r + c] = diag2[r - c + 7] = true;
        solve(r + 1);
        col[c] = diag1[r + c] = diag2[r - c + 7] = false;
    }
}

int main() {
    for (int i = 0; i < 8; i++) cin >> board[i];
    solve(0);
    cout << cnt << '\n';
}
