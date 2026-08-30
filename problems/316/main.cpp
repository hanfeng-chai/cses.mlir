#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<int> adj(n,0);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);a--;b--; if(a!=b){adj[a]|=1<<b;adj[b]|=1<<a;}}
    int full=(1<<n)-1;
    vector<char> indep(1<<n,0); indep[0]=1;
    for(int mask=1;mask<=full;mask++){ int low=__builtin_ctz(mask); int rest=mask^(1<<low); indep[mask]= indep[rest] && ((adj[low]&mask)==0); }
    const int INF=1e9;
    vector<int> dp(1<<n,INF), choice(1<<n,0);
    dp[0]=0;
    for(int mask=1;mask<=full;mask++){
        int low=__builtin_ctz(mask);
        for(int s=mask; s; s=(s-1)&mask){
            if(!(s>>low&1)) continue;
            if(!indep[s]) continue;
            if(dp[mask^s]+1 < dp[mask]){ dp[mask]=dp[mask^s]+1; choice[mask]=s; }
        }
    }
    int k=dp[full];
    vector<int> color(n,0);
    int mask=full, c=0;
    while(mask){ c++; int s=choice[mask]; for(int v=0;v<n;v++) if(s>>v&1) color[v]=c; mask^=s; }
    printf("%d\n",k);
    for(int v=0;v<n;v++) printf("%d ",color[v]);
    printf("\n");
}
