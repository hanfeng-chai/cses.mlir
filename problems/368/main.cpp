#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<int> p(n+1);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);

    // Method 1: adjacent swaps = number of inversions
    long long inversions=0;
    {
        vector<int> bit(n+1,0);
        auto upd=[&](int i){ for(;i<=n;i+=i&(-i)) bit[i]++; };
        auto qry=[&](int i){ int s=0; for(;i>0;i-=i&(-i)) s+=bit[i]; return s; };
        for(int i=n;i>=1;i--){
            inversions += qry(p[i]-1);
            upd(p[i]);
        }
    }

    // Method 2: arbitrary swaps = n - (number of cycles)
    int cycles=0;
    {
        vector<char> vis(n+1,0);
        for(int i=1;i<=n;i++){
            if(vis[i]) continue;
            cycles++;
            int j=i;
            while(!vis[j]){ vis[j]=1; j=p[j]; }
        }
    }
    long long method2 = n-cycles;

    // Method 3: move to any position = n - LIS length
    int lis=0;
    {
        vector<int> tails;
        for(int i=1;i<=n;i++){
            int v=p[i];
            auto it=lower_bound(tails.begin(),tails.end(),v);
            if(it==tails.end()) tails.push_back(v); else *it=v;
        }
        lis=(int)tails.size();
    }
    long long method3 = n-lis;

    // Method 4: move to front = n - (longest suffix of the value range n,n-1,...
    //           that appears in strictly increasing positional order)
    vector<int> pos(n+1);
    for(int i=1;i<=n;i++) pos[p[i]]=i;
    int k=1;
    for(int v=n-1; v>=1; v--){
        if(pos[v] < pos[v+1]) k++;
        else break;
    }
    long long method4 = n-k;

    printf("%lld %lld %lld %lld\n", inversions, method2, method3, method4);
}
