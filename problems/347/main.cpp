#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n);
    for(auto&v:x) scanf("%lld",&v);

    // answer = max over i of L_i = #{j<i : x_j > x_i}
    // (each element with L_i>0 moves exactly 1 step left per round while some
    //  bigger element is still to its left, so it needs exactly L_i rounds)
    vector<long long> sorted_x(x);
    sort(sorted_x.begin(), sorted_x.end());
    sorted_x.erase(unique(sorted_x.begin(), sorted_x.end()), sorted_x.end());
    int m=(int)sorted_x.size();
    vector<int> bit(m+1,0);
    auto update=[&](int pos){ for(;pos<=m;pos+=pos&(-pos)) bit[pos]++; };
    auto query=[&](int pos){ int s=0; for(;pos>0;pos-=pos&(-pos)) s+=bit[pos]; return s; };

    long long ans=0;
    for(int i=0;i<n;i++){
        int r = (int)(lower_bound(sorted_x.begin(), sorted_x.end(), x[i]) - sorted_x.begin()) + 1;
        int countGreater = i - query(r); // i inserted so far, minus those <= x[i]
        ans = max(ans, (long long)countGreater);
        update(r);
    }
    printf("%lld\n", ans);
}
