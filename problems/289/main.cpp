#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    if (n == 2) { printf("IMPOSSIBLE\n"); return 0; }  // only impossible case
    set<int> freeS;
    for (int s = 1; s <= n; s++) freeS.insert(s);
    vector<int> c(n + 1, 0), deferred;
    for (int i = 1; i <= n; i++) {  // greedily assign a free symbol != a_i, b_i
        int chosen = -1; auto it = freeS.begin();
        for (int cnt = 0; cnt < 3 && it != freeS.end(); cnt++, ++it)
            if (*it != a[i] && *it != b[i]) { chosen = *it; break; }
        if (chosen != -1) { c[i] = chosen; freeS.erase(chosen); }
        else deferred.push_back(i);  // happens only when <=2 symbols remain, both forbidden
    }
    vector<int> rem(freeS.begin(), freeS.end());
    for (int i : deferred) {
        int found = -1;
        for (int idx = 0; idx < (int)rem.size(); idx++) if (rem[idx] != -1 && rem[idx] != a[i] && rem[idx] != b[i]) { found = idx; break; }
        if (found != -1) { c[i] = rem[found]; rem[found] = -1; continue; }
        for (int j = 1; j <= n; j++) {  // swap with a matched position j
            if (c[j] == 0 || c[j] == a[i] || c[j] == b[i]) continue;
            int got = -1;
            for (int idx = 0; idx < (int)rem.size(); idx++) if (rem[idx] != -1 && rem[idx] != a[j] && rem[idx] != b[j]) { got = idx; break; }
            if (got != -1) { c[i] = c[j]; c[j] = rem[got]; rem[got] = -1; break; }
        }
    }
    string out;
    for (int i = 1; i <= n; i++) { out += to_string(c[i]); out += " \n"[i == n]; }
    cout << out;
}
