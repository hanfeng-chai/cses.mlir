#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> adj;
int chromatic(){
    int full=(1<<n)-1;
    vector<char> indep(1<<n,0); indep[0]=1;
    for(int mask=1;mask<=full;mask++){ int low=__builtin_ctz(mask); int rest=mask^(1<<low); indep[mask]= indep[rest] && ((adj[low]&mask)==0); }
    vector<int> dp(1<<n,1e9); dp[0]=0;
    for(int mask=1;mask<=full;mask++){ int low=__builtin_ctz(mask);
        for(int s=mask;s;s=(s-1)&mask){ if(!(s>>low&1))continue; if(!indep[s])continue; dp[mask]=min(dp[mask],dp[mask^s]+1); } }
    return dp[full];
}
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    n=inf.readInt(); int m=inf.readInt();
    adj.assign(n,0);
    vector<pair<int,int>> edges;
    for(int i=0;i<m;i++){int a=inf.readInt(),b=inf.readInt(); edges.push_back({a,b}); a--;b--; if(a!=b){adj[a]|=1<<b;adj[b]|=1<<a;}}
    int opt=chromatic();
    int k=ouf.readInt(1,n);
    if(k!=opt) quitf(_wa,"reported %d colors but chromatic number is %d",k,opt);
    vector<int> col(n+1);
    for(int v=1;v<=n;v++){ col[v]=ouf.readInt(1,k); }
    for(auto&e:edges) if(col[e.first]==col[e.second]) quitf(_wa,"edge %d-%d endpoints share color %d",e.first,e.second,col[e.first]);
    quitf(_ok,"valid optimal coloring with %d colors",k);
}
