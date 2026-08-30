#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int N,M;
vector<vector<pair<int,int>>> G;
vector<int> disc,low; int timer_;
bool hasBridge; int comps_;
void analyze(){
    disc.assign(N+1,0); low.assign(N+1,0); timer_=0; hasBridge=false; comps_=0;
    vector<int> it_(N+1,0);
    for(int s=1;s<=N;s++){ if(disc[s])continue; comps_++;
        vector<pair<int,int>> stk; stk.push_back({s,-1}); disc[s]=low[s]=++timer_;
        while(!stk.empty()){
            int u=stk.back().first, pe=stk.back().second;
            if(it_[u]<(int)G[u].size()){
                auto pr=G[u][it_[u]++]; int v=pr.first,id=pr.second; if(id==pe)continue;
                if(!disc[v]){disc[v]=low[v]=++timer_;stk.push_back({v,id});}
                else low[u]=min(low[u],disc[v]);
            } else { stk.pop_back(); if(!stk.empty()){int p=stk.back().first; low[p]=min(low[p],low[u]); if(low[u]>disc[p])hasBridge=true;} }
        }
    }
}
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    N=inf.readInt(); M=inf.readInt();
    G.assign(N+1,{});
    map<pair<int,int>,int> avail;
    for(int i=0;i<M;i++){int a=inf.readInt(),b=inf.readInt(); G[a].push_back({b,i}); G[b].push_back({a,i}); int x=a,y=b; if(x>y)swap(x,y); avail[{x,y}]++;}
    analyze();
    bool connected=(comps_==1);
    bool possible = connected && !hasBridge;
    string first=ouf.readToken();
    if(first=="IMPOSSIBLE"){
        if(possible) quitf(_wa,"said IMPOSSIBLE but a strong orientation exists");
        quitf(_ok,"correctly IMPOSSIBLE");
    }
    if(!possible) quitf(_wa,"gave an orientation but none exists");
    // first token is first integer of edge 1
    int a1=atoi(first.c_str());
    vector<vector<int>> dg(N+1);
    for(int i=0;i<M;i++){ int a = (i==0? a1 : ouf.readInt(1,N)); int b=ouf.readInt(1,N);
        int x=a,y=b; if(x>y)swap(x,y); auto it=avail.find({x,y}); if(it==avail.end()||it->second==0) quitf(_wa,"edge %d %d not an unused input edge",a,b); it->second--; dg[a].push_back(b); }
    // strong connectivity: BFS from 1 forward and backward
    vector<vector<int>> rg(N+1);
    for(int u=1;u<=N;u++) for(int v:dg[u]) rg[v].push_back(u);
    auto reachAll=[&](vector<vector<int>>&gr)->bool{ vector<char> vs(N+1,0); int c=0; vector<int> s={1}; vs[1]=1; while(!s.empty()){int u=s.back();s.pop_back();c++;for(int v:gr[u])if(!vs[v]){vs[v]=1;s.push_back(v);}} return c==N; };
    if(!reachAll(dg) || !reachAll(rg)) quitf(_wa,"orientation is not strongly connected");
    quitf(_ok,"valid strong orientation");
}
