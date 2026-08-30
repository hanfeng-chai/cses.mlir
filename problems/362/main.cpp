#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n+1);
    for(int i=1;i<=n;i++) scanf("%lld",&x[i]);

    // compress values to ranks 1..n (values are distinct but not necessarily 1..n)
    vector<long long> sorted_x(x.begin()+1, x.end());
    sort(sorted_x.begin(), sorted_x.end());
    vector<int> rank(n+1);
    for(int i=1;i<=n;i++)
        rank[i] = (int)(lower_bound(sorted_x.begin(), sorted_x.end(), x[i]) - sorted_x.begin()) + 1;

    vector<int> pos(n+1); // pos[rank] = position
    for(int i=1;i<=n;i++) pos[rank[i]]=i;

    vector<long long> bit(n+2,0);
    auto update=[&](int p){ for(;p<=n;p+=p&(-p)) bit[p]++; };
    auto query=[&](int p){ long long s=0; for(;p>0;p-=p&(-p)) s+=bit[p]; return s; };

    update(pos[n]); // insert the global maximum first (it is always "larger" than everything else)
    long long totalInserted=1;
    long long ans=0;
    for(int v=n-1; v>=1; v--){
        int p = pos[v];
        long long costL = query(p);            // larger elements to its left
        long long costR = totalInserted - costL; // larger elements to its right
        ans += min(costL, costR);
        update(p);
        totalInserted++;
    }
    printf("%lld\n", ans);
}
