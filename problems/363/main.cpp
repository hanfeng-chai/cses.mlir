#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<int> a(n+1), posA(n+1), posB(m+1);
    for(int i=1;i<=n;i++){ scanf("%d",&a[i]); posA[a[i]]=i; }
    vector<int> b(m+1);
    for(int i=1;i<=m;i++){ scanf("%d",&b[i]); posB[b[i]]=i; }

    // scan a left to right, keep values <= m, build sequence of posB
    vector<int> vals, seq;
    for(int i=1;i<=n;i++) if(a[i]<=m){ vals.push_back(a[i]); seq.push_back(posB[a[i]]); }

    int k=(int)seq.size();
    vector<int> tails; // values
    vector<int> tailsIdx; // index in seq for each tail entry
    vector<int> prevIdx(k, -1);
    vector<int> posInTails(k, -1); // for each seq index, which tails-slot it occupies

    for(int i=0;i<k;i++){
        int v=seq[i];
        int lo=0, hi=(int)tails.size();
        while(lo<hi){ int mid=(lo+hi)/2; if(tails[mid]<v) lo=mid+1; else hi=mid; }
        if(lo>0) prevIdx[i]=tailsIdx[lo-1];
        if(lo==(int)tails.size()){ tails.push_back(v); tailsIdx.push_back(i); }
        else { tails[lo]=v; tailsIdx[lo]=i; }
    }

    int L=(int)tails.size();
    vector<int> resIdx;
    int cur = L>0 ? tailsIdx.back() : -1;
    while(cur!=-1){ resIdx.push_back(cur); cur=prevIdx[cur]; }
    reverse(resIdx.begin(), resIdx.end());

    printf("%d\n", L);
    string out;
    for(int idx: resIdx){ out += to_string(vals[idx]); out += ' '; }
    if(!out.empty()) out.back()='\n'; else out="\n";
    fputs(out.c_str(), stdout);
}
