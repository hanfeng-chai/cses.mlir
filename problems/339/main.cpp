#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n; scanf("%d",&n);
    // rounds = 1 + #{i: pos(i+1)<pos(i)} = 1 + descents(pos); count = Eulerian A(n, k-1)
    vector<long long> E(n+1,0); E[0]=1; // A(1,0)=1 after first iter
    // build Eulerian for size n
    vector<long long> cur(n+1,0); cur[0]=1; // size 1: A(1,0)=1
    for(int i=2;i<=n;i++){
        vector<long long> nx(n+1,0);
        for(int d=0;d<i;d++){
            long long v=( (long long)(d+1)*cur[d] + (long long)(i-d)* (d>0?cur[d-1]:0) )%MOD;
            nx[d]=v;
        }
        cur.swap(nx);
    }
    // cur[d] = A(n,d); answer for k = A(n,k-1)
    string out; out.reserve(n*7);
    for(int k=1;k<=n;k++){ out+=to_string(cur[k-1]%MOD); out+=' '; }
    out+='\n';
    fputs(out.c_str(),stdout);
}
