#include <bits/stdc++.h>
using namespace std;
static char ibuf[1<<23]; int ipos=0, ilen=0;
inline int rdint(){ while(ipos<ilen && (ibuf[ipos]<'0'||ibuf[ipos]>'9')) ipos++; int x=0; while(ipos<ilen && ibuf[ipos]>='0'&&ibuf[ipos]<='9'){x=x*10+ibuf[ipos]-'0';ipos++;} return x; }
int n,d;
vector<int> adjStart, adjList;
vector<int> sz_, par_, ord_, bq_, cdist_, bpar_;
vector<char> removed, vis;
vector<int> tu, tc, td;            // (vertex, centroid, dist) triples
vector<int> off, fC, fD;           // flattened per-vertex centroid-ancestor lists
vector<int> bestDist;
const int INF=1e9;

void decompose(int start){
    int L=0;
    { int h=0,t=0; bq_[t++]=start; vis[start]=1; par_[start]=-1;
      while(h<t){int u=bq_[h++]; ord_[L++]=u; for(int i=adjStart[u];i<adjStart[u+1];i++){int v=adjList[i]; if(!removed[v]&&!vis[v]){vis[v]=1;par_[v]=u;bq_[t++]=v;}}} }
    int tot=L;
    for(int i=0;i<L;i++) sz_[ord_[i]]=1;
    for(int i=L-1;i>=1;i--){ int u=ord_[i]; sz_[par_[u]]+=sz_[u]; }
    int cur=start, pcur=-1;
    while(true){ int nxt=-1;
        for(int i=adjStart[cur];i<adjStart[cur+1];i++){ int v=adjList[i]; if(!removed[v]&&v!=pcur){ int s=(par_[v]==cur)? sz_[v] : (tot - sz_[cur]); if(s>tot/2){ nxt=v; break; } } }
        if(nxt==-1) break;
        pcur=cur; cur=nxt; }
    int c=cur;
    { int h=0,t=0; bq_[t++]=c; cdist_[c]=0; bpar_[c]=-1;
      while(h<t){int u=bq_[h++]; tu.push_back(u); tc.push_back(c); td.push_back(cdist_[u]); for(int i=adjStart[u];i<adjStart[u+1];i++){int v=adjList[i]; if(!removed[v]&&v!=bpar_[u]){bpar_[v]=u;cdist_[v]=cdist_[u]+1;bq_[t++]=v;}}} }
    for(int i=0;i<L;i++) vis[ord_[i]]=0;
    removed[c]=1;
    for(int i=adjStart[c];i<adjStart[c+1];i++){ int v=adjList[i]; if(!removed[v]) decompose(v); }
}
int query(int v){ int res=INF; for(int i=off[v];i<off[v+1];i++){ if(bestDist[fC[i]]<INF) res=min(res, fD[i]+bestDist[fC[i]]); } return res; }
void update(int v){ for(int i=off[v];i<off[v+1];i++){ if(fD[i]<bestDist[fC[i]]) bestDist[fC[i]]=fD[i]; } }

int main(){
    ilen=fread(ibuf,1,sizeof(ibuf),stdin);
    n=rdint(); d=rdint();
    vector<int> ea(n-1), eb(n-1), deg(n+2,0);
    for(int i=0;i<n-1;i++){int a=rdint(),b=rdint();ea[i]=a;eb[i]=b;deg[a]++;deg[b]++;}
    adjStart.assign(n+2,0);
    for(int u=1;u<=n;u++) adjStart[u+1]=adjStart[u]+deg[u];
    adjList.assign(2*(n-1>0?n-1:0),0);
    {vector<int> pos(adjStart.begin(),adjStart.end());
     for(int i=0;i<n-1;i++){ adjList[pos[ea[i]]++]=eb[i]; adjList[pos[eb[i]]++]=ea[i]; }}
    removed.assign(n+1,0); vis.assign(n+1,0); sz_.assign(n+1,0); par_.assign(n+1,0);
    ord_.assign(n+1,0); bq_.assign(n+1,0); cdist_.assign(n+1,0); bpar_.assign(n+1,0);
    bestDist.assign(n+1,INF);
    tu.reserve((size_t)n*20); tc.reserve((size_t)n*20); td.reserve((size_t)n*20);
    decompose(1);
    int total=tu.size();
    off.assign(n+2,0);
    for(int i=0;i<total;i++) off[tu[i]+1]++;
    for(int v=1;v<=n;v++) off[v+1]+=off[v];
    fC.resize(total); fD.resize(total);
    {vector<int> p(off.begin(),off.end());
     for(int i=0;i<total;i++){ int v=tu[i]; int pos=p[v]++; fC[pos]=tc[i]; fD[pos]=td[i]; }}
    vector<int> depth(n+1,-1);
    {int h=0,t=0; vector<int> q(n); q[t++]=1; depth[1]=0; while(h<t){int u=q[h++];for(int i=adjStart[u];i<adjStart[u+1];i++){int v=adjList[i];if(depth[v]<0){depth[v]=depth[u]+1;q[t++]=v;}}}}
    vector<int> order(n); for(int i=0;i<n;i++) order[i]=i+1;
    sort(order.begin(),order.end(),[&](int a,int b){return depth[a]>depth[b];});
    vector<int> chosen;
    for(int u: order){ if(query(u) >= d){ chosen.push_back(u); update(u); } }
    printf("%d\n",(int)chosen.size());
    string out; out.reserve(chosen.size()*7);
    for(int x:chosen){ out+=to_string(x); out+=' '; }
    out+='\n';
    fputs(out.c_str(),stdout);
}
