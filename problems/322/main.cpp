#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);}
    // iterative Tarjan SCC
    vector<int> comp(n+1,-1), low(n+1,0), disc(n+1,0), it_(n+1,0), stk; vector<char> onstk(n+1,0);
    int timer=0, q=0;
    for(int s=1;s<=n;s++){
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
            if(low[u]==disc[u]){ while(true){int x=stk.back();stk.pop_back();onstk[x]=0;comp[x]=q; if(x==u)break;} q++; }
            dfs.pop_back();
            if(!dfs.empty()){ int p=dfs.back(); low[p]=min(low[p],low[u]); }
        }
    }
    if(q==1){ printf("0\n"); return 0; }
    // condensation
    vector<int> rep(q,0);
    for(int v=1;v<=n;v++) rep[comp[v]]=v;
    vector<char> hasIn(q,0), hasOut(q,0);
    vector<vector<int>> cadj(q);
    {
        vector<pair<int,int>> es;
        for(int u=1;u<=n;u++) for(int v:g[u]){ int cu=comp[u],cv=comp[v]; if(cu!=cv) es.push_back({cu,cv}); }
        sort(es.begin(),es.end()); es.erase(unique(es.begin(),es.end()),es.end());
        for(auto&e:es){ cadj[e.first].push_back(e.second); hasOut[e.first]=1; hasIn[e.second]=1; }
    }
    vector<int> sources, sinks;
    for(int c=0;c<q;c++){ if(!hasIn[c]) sources.push_back(c); if(!hasOut[c]) sinks.push_back(c); }
    // greedy pairing source -> reachable unused sink (global visited, iterative DFS)
    vector<char> vis(q,0); vector<int> ptr(q,0);
    vector<pair<int,int>> pairs; // (sourceSCC, sinkSCC)
    vector<char> pairedSink(q,0), pairedSrc(q,0);
    for(int v: sources){
        if(vis[v]) continue;
        vector<int> st={v}; vis[v]=1; int foundSink=-1;
        while(!st.empty()){
            int u=st.back();
            if(!hasOut[u]){ foundSink=u; break; }
            bool adv=false;
            while(ptr[u] < (int)cadj[u].size()){
                int w=cadj[u][ptr[u]++];
                if(!vis[w]){ vis[w]=1; st.push_back(w); adv=true; break; }
            }
            if(!adv) st.pop_back();
        }
        if(foundSink!=-1){ pairs.push_back({v,foundSink}); pairedSrc[v]=1; pairedSink[foundSink]=1; }
    }
    vector<int> remSources, remSinks;
    for(int c: sources) if(!pairedSrc[c]) remSources.push_back(c);
    for(int c: sinks) if(!pairedSink[c]) remSinks.push_back(c);
    int p=pairs.size();
    vector<pair<int,int>> out; // edges (origVertexFrom, origVertexTo)
    // cycle through pairs: sink_i -> src_{(i+1)%p}
    for(int i=0;i<p;i++){
        int sinkSCC=pairs[i].second, srcSCC=pairs[(i+1)%p].first;
        out.push_back({rep[sinkSCC], rep[srcSCC]});
    }
    int hubSink=pairs[0].second, hubSrc=pairs[0].first;
    int i=0,j=0;
    while(i<(int)remSources.size() && j<(int)remSinks.size()){
        out.push_back({rep[remSinks[j]], rep[remSources[i]]});
        i++; j++;
    }
    while(i<(int)remSources.size()){ out.push_back({rep[hubSink], rep[remSources[i]]}); i++; }
    while(j<(int)remSinks.size()){ out.push_back({rep[remSinks[j]], rep[hubSrc]}); j++; }
    printf("%d\n",(int)out.size());
    string res; res.reserve(out.size()*12);
    for(auto&e:out){ res+=to_string(e.first); res+=' '; res+=to_string(e.second); res+='\n'; }
    fputs(res.c_str(),stdout);
}
