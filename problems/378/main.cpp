#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<int> p(n+1);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);

    vector<int> cur(n+1);
    for(int i=1;i<=n;i++) cur[i]=p[i];

    vector<char> visited(n+1,0);
    vector<pair<int,int>> round1, round2;
    vector<int> posInCycle(n+1,-1); // allocated once; entries only read for the current cycle

    for(int start=1; start<=n; start++){
        if(visited[start]) continue;
        vector<int> indices;
        int x=start;
        do{ indices.push_back(x); visited[x]=1; x=cur[x]; } while(x!=start);
        int L=(int)indices.size();
        if(L<=1) continue;
        if(L==2){ round1.push_back({indices[0], indices[1]}); continue; }

        // any cycle of length >= 3 can be sorted in exactly 2 rounds:
        // round1 = "fold in half" (swap i with L-1-i), round2 = whatever mutual swaps remain.
        for(int i=0;i<L;i++) posInCycle[indices[i]]=i;
        for(int i=0; i<L-1-i; i++){
            int a=indices[i], b=indices[L-1-i];
            round1.push_back({a,b});
            swap(cur[a], cur[b]);
        }
        vector<char> done(L,0);
        for(int i=0;i<L;i++){
            int pos=indices[i];
            if(done[i] || cur[pos]==pos) continue;
            int target=cur[pos];
            round2.push_back({pos, target});
            done[i]=1;
            done[posInCycle[target]]=1;
        }
    }

    vector<vector<pair<int,int>>> rounds;
    if(!round1.empty()) rounds.push_back(round1);
    if(!round2.empty()) rounds.push_back(round2);

    printf("%d\n", (int)rounds.size());
    string out;
    for(auto& rnd: rounds){
        out += to_string(rnd.size()); out += '\n';
        for(auto& sw: rnd){ out += to_string(sw.first); out+=' '; out+=to_string(sw.second); out+='\n'; }
    }
    fputs(out.c_str(), stdout);
}

