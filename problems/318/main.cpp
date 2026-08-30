#include <bits/stdc++.h>
using namespace std;
static char ibuf[1<<24]; int ipos=0, ilen=0;
inline int rdint(){ while(ipos<ilen && (ibuf[ipos]<'0'||ibuf[ipos]>'9')) ipos++; int x=0; while(ipos<ilen && ibuf[ipos]>='0'&&ibuf[ipos]<='9'){x=x*10+ibuf[ipos]-'0';ipos++;} return x; }
int N;
vector<int> adjStart, adjList;
vector<int> matchL, matchR, distA, iterA, bfsq;
bool bfs(){
    int head=0,tail=0;
    for(int u=1;u<=N;u++){ if(!matchL[u]){distA[u]=0;bfsq[tail++]=u;} else distA[u]=-1; }
    bool found=false;
    while(head<tail){ int u=bfsq[head++]; for(int i=adjStart[u];i<adjStart[u+1];i++){ int v=adjList[i]; int w=matchR[v]; if(!w) found=true; else if(distA[w]<0){distA[w]=distA[u]+1;bfsq[tail++]=w;} } }
    return found;
}
bool dfs(int u){
    for(int &i=iterA[u]; i<adjStart[u+1]; i++){ int v=adjList[i]; int w=matchR[v]; if(!w||(distA[w]==distA[u]+1&&dfs(w))){matchL[u]=v;matchR[v]=u;return true;} }
    return false;
}
int main(){
    ilen=fread(ibuf,1,sizeof(ibuf),stdin);
    int n=rdint(), m=rdint(); N=n;
    vector<int> ea(m), eb(m), deg(n+2,0);
    for(int i=0;i<m;i++){int a=rdint(),b=rdint();ea[i]=a;eb[i]=b;deg[a]++;}
    adjStart.assign(n+2,0);
    for(int u=1;u<=n;u++) adjStart[u+1]=adjStart[u]+deg[u];
    adjList.assign(m,0);
    {vector<int> pos(adjStart.begin(),adjStart.end());
     for(int i=0;i<m;i++){ adjList[pos[ea[i]]++]=eb[i]; }}
    matchL.assign(n+1,0); matchR.assign(n+1,0); distA.assign(n+1,0); iterA.assign(n+1,0); bfsq.assign(n+1,0);
    int matching=0;
    while(bfs()){ for(int u=1;u<=n;u++) iterA[u]=adjStart[u]; for(int u=1;u<=n;u++) if(!matchL[u] && dfs(u)) matching++; }
    int cover=n-matching;
    if(cover>2){ printf("NO\n"); return 0; }
    printf("YES\n");
    vector<vector<int>> paths;
    for(int u=1;u<=n;u++) if(matchR[u]==0){
        vector<int> p; int cur=u; while(cur){ p.push_back(cur); cur=matchL[cur]; }
        paths.push_back(p);
    }
    for(int i=0;i<2;i++){
        if(i<(int)paths.size()){ printf("%d", (int)paths[i].size()); for(int x:paths[i]) printf(" %d",x); printf("\n"); }
        else printf("0\n");
    }
}
