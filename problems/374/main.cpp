#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; long long k; scanf("%d %lld",&n,&k);
    vector<long long> x(n);
    long long base=0;
    for(auto&v:x){ scanf("%lld",&v); if(v<0) base+=v; }

    vector<long long> Y(n);
    for(int i=0;i<n;i++) Y[i]=llabs(x[i]);
    sort(Y.begin(), Y.end());

    vector<long long> res;
    res.push_back(base); // empty subset

    if(k>1){
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> heap;
        heap.push({Y[0], 0});
        while((long long)res.size()<k && !heap.empty()){
            auto [s,idx] = heap.top(); heap.pop();
            res.push_back(base+s);
            if((long long)res.size()>=k) break;
            if(idx+1<n){
                heap.push({s+Y[idx+1], idx+1});
                heap.push({s-Y[idx]+Y[idx+1], idx+1});
            }
        }
    }

    string out; out.reserve(res.size()*7);
    for(int i=0;i<(int)k;i++){ out += to_string(res[i]); out+=' '; }
    out += '\n';
    fputs(out.c_str(), stdout);
}
