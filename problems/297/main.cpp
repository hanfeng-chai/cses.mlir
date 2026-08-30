#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<int> pre(n), in(n);
    for(auto&x:pre)scanf("%d",&x);
    for(auto&x:in)scanf("%d",&x);
    if(n==0){ printf("\n"); return 0; }
    vector<int> L(n+1,0), R(n+1,0);
    vector<int> st; st.reserve(n+1);
    st.push_back(pre[0]);
    int inIdx=0;
    for(int i=1;i<n;i++){
        int node=pre[i], last=-1;
        if(st.back()!=in[inIdx]) L[st.back()]=node;
        else { while(!st.empty() && st.back()==in[inIdx]){ last=st.back(); st.pop_back(); inIdx++; } R[last]=node; }
        st.push_back(node);
    }
    vector<int> out; out.reserve(n);
    vector<pair<int,int>> stk; stk.reserve(n+5);
    stk.push_back({pre[0],0});
    while(!stk.empty()){
        int idx=stk.size()-1; int u=stk[idx].first, s=stk[idx].second;
        if(s==0){ stk[idx].second=1; if(L[u]) stk.push_back({L[u],0}); }
        else if(s==1){ stk[idx].second=2; if(R[u]) stk.push_back({R[u],0}); }
        else { out.push_back(u); stk.pop_back(); }
    }
    for(int i=0;i<n;i++) printf("%d ", out[i]);
    printf("\n");
}
