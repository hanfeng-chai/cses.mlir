#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int N; vector<vector<pair<int,int>>> G; vector<int> disc,low; int timer_; int bridges;
void analyze(){
    disc.assign(N+1,0); low.assign(N+1,0); timer_=0; bridges=0;
    vector<int> it_(N+1,0);
    for(int s=1;s<=N;s++){ if(disc[s])continue;
        vector<pair<int,int>> stk; stk.push_back({s,-1}); disc[s]=low[s]=++timer_;
        while(!stk.empty()){
            int u=stk.back().first, pe=stk.back().second;
            if(it_[u]<(int)G[u].size()){ auto pr=G[u][it_[u]++]; int v=pr.first,id=pr.second; if(id==pe)continue;
                if(!disc[v]){disc[v]=low[v]=++timer_;stk.push_back({v,id});} else low[u]=min(low[u],disc[v]); }
            else { stk.pop_back(); if(!stk.empty()){int p=stk.back().first; low[p]=min(low[p],low[u]); if(low[u]>disc[p])bridges++;} }
        }
    }
}
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    N=inf.readInt();
    vector<int> deg(N+1,0);
    G.assign(N+1,{});
    int eid=0;
    for(int i=0;i<N-1;i++){int a=inf.readInt(),b=inf.readInt(); G[a].push_back({b,eid});G[b].push_back({a,eid});eid++; deg[a]++;deg[b]++;}
    int leaves=0; for(int v=1;v<=N;v++) if(deg[v]==1) leaves++;
    int need=(leaves+1)/2;
    int k=ouf.readInt(0,N);
    if(k!=need) quitf(_wa,"reported %d new edges but minimum is %d (leaves=%d)",k,need,leaves);
    for(int i=0;i<k;i++){ int a=ouf.readInt(1,N), b=ouf.readInt(1,N); G[a].push_back({b,eid}); G[b].push_back({a,eid}); eid++; }
    analyze();
    bool connected=true; for(int v=1;v<=N;v++) if(!disc[v]){connected=false;break;}
    if(!connected) quitf(_wa,"graph not connected after adding edges");
    if(bridges>0) quitf(_wa,"graph still has %d bridge(s) after adding edges",bridges);
    quitf(_ok,"valid: %d edges, 2-edge-connected",k);
}
