#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> B;

vector<long long> tryReconstruct(long long a1){
    if(a1<=0) return {};
    multiset<long long> ms(B.begin(), B.end());
    auto take=[&](long long v)->bool{
        auto it=ms.find(v);
        if(it==ms.end()) return false;
        ms.erase(it);
        return true;
    };
    if(!take(B[0])) return {};
    long long a2 = B[0]-a1;
    if(a2 < a1) return {};
    vector<long long> A = {a1, a2};
    while((int)A.size() < n){
        if(ms.empty()) return {};
        long long s = *ms.begin();
        long long newv = s - a1;
        if(!take(s)) return {};
        for(size_t k=1;k<A.size();k++){
            if(!take(A[k]+newv)) return {};
        }
        A.push_back(newv);
    }
    if(!ms.empty()) return {};
    return A;
}

int main(){
    scanf("%d",&n);
    int m = n*(n-1)/2;
    B.resize(m);
    for(auto&v:B) scanf("%lld",&v);
    sort(B.begin(), B.end());

    int lim = min(m, 300);
    set<long long> tried;
    vector<long long> ans;
    for(int i=0;i<lim && ans.empty();i++){
        long long num = B[0]+B[1]-B[i];
        if(num<=0 || num%2!=0) continue;
        long long a1 = num/2;
        if(tried.count(a1)) continue;
        tried.insert(a1);
        auto res = tryReconstruct(a1);
        if(!res.empty()) ans = res;
    }

    string out;
    for(long long v: ans){ out += to_string(v); out += ' '; }
    if(!out.empty()) out.back()='\n';
    fputs(out.c_str(), stdout);
}
