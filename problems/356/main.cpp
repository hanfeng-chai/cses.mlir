#include <bits/stdc++.h>
using namespace std;

int A,B;
inline int idx(int a,int b){ return a*(B+1)+b; }

int main(){
    long long a,b,x; scanf("%lld %lld %lld",&a,&b,&x);
    if(x>a){ printf("-1\n"); return 0; }
    A=(int)a; B=(int)b;
    int NS = (A+1)*(B+1);
    vector<long long> dist(NS, LLONG_MAX);
    vector<int> parentState(NS,-1), parentMove(NS,-1);

    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    int start = idx(0,0);
    dist[start]=0;
    pq.push({0,start});

    while(!pq.empty()){
        auto top = pq.top(); pq.pop();
        long long d=top.first; int s=top.second;
        if(d>dist[s]) continue;
        int ca=s/(B+1), cb=s%(B+1);

        // (target state, cost, move id)  0=FILLA 1=FILLB 2=EMPTYA 3=EMPTYB 4=MOVEAB 5=MOVEBA
        int na,nb; long long cost; int mv;

        if(ca<A){
            na=A; nb=cb; cost=A-ca; mv=0;
            int ns=idx(na,nb); long long nd=d+cost;
            if(nd<dist[ns]){ dist[ns]=nd; parentState[ns]=s; parentMove[ns]=mv; pq.push({nd,ns}); }
        }
        if(cb<B){
            na=ca; nb=B; cost=B-cb; mv=1;
            int ns=idx(na,nb); long long nd=d+cost;
            if(nd<dist[ns]){ dist[ns]=nd; parentState[ns]=s; parentMove[ns]=mv; pq.push({nd,ns}); }
        }
        if(ca>0){
            na=0; nb=cb; cost=ca; mv=2;
            int ns=idx(na,nb); long long nd=d+cost;
            if(nd<dist[ns]){ dist[ns]=nd; parentState[ns]=s; parentMove[ns]=mv; pq.push({nd,ns}); }
        }
        if(cb>0){
            na=ca; nb=0; cost=cb; mv=3;
            int ns=idx(na,nb); long long nd=d+cost;
            if(nd<dist[ns]){ dist[ns]=nd; parentState[ns]=s; parentMove[ns]=mv; pq.push({nd,ns}); }
        }
        {
            long long amt=min(ca, B-cb);
            if(amt>0){
                na=ca-(int)amt; nb=cb+(int)amt; cost=amt; mv=4;
                int ns=idx(na,nb); long long nd=d+cost;
                if(nd<dist[ns]){ dist[ns]=nd; parentState[ns]=s; parentMove[ns]=mv; pq.push({nd,ns}); }
            }
        }
        {
            long long amt=min(cb, A-ca);
            if(amt>0){
                na=ca+(int)amt; nb=cb-(int)amt; cost=amt; mv=5;
                int ns=idx(na,nb); long long nd=d+cost;
                if(nd<dist[ns]){ dist[ns]=nd; parentState[ns]=s; parentMove[ns]=mv; pq.push({nd,ns}); }
            }
        }
    }

    long long best=LLONG_MAX; int bestState=-1;
    for(int cb=0;cb<=B;cb++){
        int s=idx((int)x,cb);
        if(dist[s]<best){ best=dist[s]; bestState=s; }
    }

    if(bestState==-1 || best==LLONG_MAX){ printf("-1\n"); return 0; }

    vector<int> moves;
    int cur=bestState;
    while(cur!=start){
        moves.push_back(parentMove[cur]);
        cur=parentState[cur];
    }
    reverse(moves.begin(),moves.end());

    printf("%d %lld\n", (int)moves.size(), best);
    string out;
    for(int mv: moves){
        switch(mv){
            case 0: out+="FILL A\n"; break;
            case 1: out+="FILL B\n"; break;
            case 2: out+="EMPTY A\n"; break;
            case 3: out+="EMPTY B\n"; break;
            case 4: out+="MOVE A B\n"; break;
            case 5: out+="MOVE B A\n"; break;
        }
    }
    fputs(out.c_str(), stdout);
}
