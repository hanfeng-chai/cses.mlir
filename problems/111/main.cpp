#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    if (n == 1) { printf("01\n"); return 0; }
    int bits = n - 1, V = 1 << bits, mask = V - 1;
    // De Bruijn graph: node = (n-1)-bit value; edge with label l goes to ((u<<1)|l)&mask
    vector<int> ptr(V, 0), circuit;
    vector<int> stk = {0};
    while (!stk.empty()) {
        int u = stk.back();
        if (ptr[u] < 2) {
            int l = ptr[u]++;
            stk.push_back(((u << 1) | l) & mask);
        } else { circuit.push_back(u); stk.pop_back(); }
    }
    reverse(circuit.begin(), circuit.end());
    string res(bits, '0');  // start node 0 = (n-1) zeros
    for (size_t i = 1; i < circuit.size(); i++) res += char('0' + (circuit[i] & 1));
    printf("%s\n", res.c_str());
}
