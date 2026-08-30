#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int N;
vector<vector<int>> g;
// iterative Tarjan SCC -> returns (comp array, count)
pair<vector<int>,int> scc(){
    vector<int> comp(N+1,-1), low(N+1,0), disc(N+1,0), it_(N+1,0), stk; vector<char> onstk(N+1,0);
    int timer=0, cnt=0;
    for(int s=1;s<=N;s++){
        if(disc[s]) continue;
        vector<int> dfs; dfs.push_back(s);
        while(!dfs.empty()){
            int u=dfs.back();
            if(!disc[u]){ disc[u]=low[u]=++timer; stk.push_back(u); onstk[u]=1; }
            bool pushed=false;
            while(it_[u]<(int)g[u].size()){
                int w=g[u][it_[u]++];
                if(!disc[w]){ dfs.push_back(w); pushed=true; break; }
                else if(onstk[w]) low[u]=min(low[u],disc[w]);
            }
            if(pushed) continue;
            if(low[u]==disc[u]){ while(true){int x=stk.back();stk.pop_back();onstk[x]=0;comp[x]=cnt; if(x==u)break;} cnt++; }
            dfs.pop_back();
            if(!dfs.empty()){ int p=dfs.back(); low[p]=min(low[p],low[u]); }
        }
    }
    return {comp,cnt};
}
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int n=inf.readInt(), m=inf.readInt(); N=n;
    g.assign(n+1,{});
    for(int i=0;i<m;i++){int a=inf.readInt(),b=inf.readInt(); g[a].push_back(b);}
    auto pr=scc(); auto comp=pr.first; int q=pr.second;
    int minAns;
    if(q==1) minAns=0;
    else {
        vector<char> hasIn(q,0), hasOut(q,0);
        for(int u=1;u<=n;u++) for(int v: g[u]){ int cu=comp[u],cv=comp[v]; if(cu!=cv){ hasOut[cu]=1; hasIn[cv]=1; } }
        int sources=0,sinks=0; for(int c=0;c<q;c++){ if(!hasIn[c])sources++; if(!hasOut[c])sinks++; }
        minAns=max(sources,sinks);
    }
    int k=ouf.readInt(0, 2*n+10);
    if(k!=minAns) quitf(_wa,"reported %d new flights but minimum is %d",k,minAns);
    for(int i=0;i<k;i++){ int a=ouf.readInt(1,n), b=ouf.readInt(1,n); g[a].push_back(b); }
    auto pr2=scc(); int q2=pr2.second;
    if(n>=1 && q2!=1) quitf(_wa,"graph is not strongly connected after adding %d edges (%d SCCs)",k,q2);
    quitf(_ok,"valid: %d edges, strongly connected",k);
}
