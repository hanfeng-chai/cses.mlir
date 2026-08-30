#include <bits/stdc++.h>
using namespace std;

static const int FACT[10]={1,1,2,6,24,120,720,5040,40320,362880};

int rankOf(const array<int,9>&a){
    int r=0;
    for(int i=0;i<9;i++){
        int smaller=0;
        for(int j=i+1;j<9;j++) if(a[j]<a[i]) smaller++;
        r += smaller*FACT[8-i];
    }
    return r;
}

int main(){
    array<int,9> start;
    for(int i=0;i<9;i++) scanf("%d",&start[i]);
    const array<int,9> target={1,2,3,4,5,6,7,8,9};
    int targetRank = rankOf(target);
    int startRank = rankOf(start);
    if(startRank==targetRank){ printf("0\n"); return 0; }

    static vector<int> dist(362880,-1);
    dist[startRank]=0;
    queue<array<int,9>> q;
    q.push(start);
    static const int adj[12][2] = {{0,1},{1,2},{3,4},{4,5},{6,7},{7,8},{0,3},{3,6},{1,4},{4,7},{2,5},{5,8}};

    while(!q.empty()){
        array<int,9> cur=q.front(); q.pop();
        int cr=rankOf(cur);
        int cd=dist[cr];
        for(auto&pr: adj){
            array<int,9> nx=cur;
            swap(nx[pr[0]],nx[pr[1]]);
            int nr=rankOf(nx);
            if(dist[nr]==-1){
                dist[nr]=cd+1;
                if(nr==targetRank){ printf("%d\n", dist[nr]); return 0; }
                q.push(nx);
            }
        }
    }
}
