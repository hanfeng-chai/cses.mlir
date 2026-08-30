#include <bits/stdc++.h>
using namespace std;

int par[100005];
int find(int x){ return par[x]==x ? x : par[x]=find(par[x]); }
void uni(int a,int b){ a=find(a); b=find(b); if(a!=b) par[a]=b; }

int main(){
    int n,m; scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) par[i]=i;
    for(int i=0;i<m;i++){ int a,b; scanf("%d %d",&a,&b); uni(a,b); }

    vector<int> compSize(n+1,0);
    for(int i=1;i<=n;i++) compSize[find(i)]++;

    vector<int> sizes;
    for(int i=1;i<=n;i++) if(find(i)==i) sizes.push_back(compSize[i]);

    // subset-sum reachability via bitset
    vector<uint64_t> dp((n/64)+1, 0);
    dp[0] = 1ULL; // sum 0 reachable
    for(int s: sizes){
        int wordShift = s/64, bitShift = s%64;
        int W=(int)dp.size();
        if(bitShift==0){
            for(int w=W-1; w>=wordShift; w--) dp[w] |= dp[w-wordShift];
        } else {
            for(int w=W-1; w>=wordShift; w--){
                uint64_t lo = dp[w-wordShift] << bitShift;
                uint64_t hi = (w-wordShift-1>=0) ? (dp[w-wordShift-1] >> (64-bitShift)) : 0ULL;
                dp[w] |= (lo | hi);
            }
        }
    }

    string out(n, '0');
    for(int cnt=1; cnt<=n; cnt++){
        int w=cnt/64, b=cnt%64;
        if( (dp[w] >> b) & 1ULL ) out[cnt-1]='1';
    }
    out += '\n';
    fputs(out.c_str(), stdout);
}
