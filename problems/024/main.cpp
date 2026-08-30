#include <bits/stdc++.h>
using namespace std;

// 7x7 棋盘嵌入 9x9 数组，四周一圈墙作为哨兵边界，省去越界判断。
// 行 r 向下增，列 c 向右增；真实格子 r,c ∈ [1,7]。
// 起点 = 左上 (1,1)，终点 = 左下 (7,1)。
bool wall[9][9];
string s;
long long ans = 0;

void dfs(int r, int c, int step) {
    if (r == 7 && c == 1) {            // 到达终点
        if (step == 48) ++ans;        // 恰好走满 48 步（=访问 49 格）才合法
        return;                       // 提前到达终点：剪枝（不能穿过终点继续）
    }
    bool up = wall[r - 1][c], dn = wall[r + 1][c];
    bool lf = wall[r][c - 1], rt = wall[r][c + 1];
    // 分割剪枝：一个方向两侧都是墙、另一方向两侧都空 -> 空白区被切成两块
    if ((up && dn && !lf && !rt) || (lf && rt && !up && !dn)) return;

    wall[r][c] = true;                // 占用当前格
    char d = s[step];
    if ((d == 'U' || d == '?') && !wall[r - 1][c]) dfs(r - 1, c, step + 1);
    if ((d == 'D' || d == '?') && !wall[r + 1][c]) dfs(r + 1, c, step + 1);
    if ((d == 'L' || d == '?') && !wall[r][c - 1]) dfs(r, c - 1, step + 1);
    if ((d == 'R' || d == '?') && !wall[r][c + 1]) dfs(r, c + 1, step + 1);
    wall[r][c] = false;               // 回溯
}

int main() {
    cin >> s;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            wall[i][j] = (i == 0 || i == 8 || j == 0 || j == 8);  // 边界设墙
    dfs(1, 1, 0);                     // 从左上角出发
    cout << ans << '\n';
}


