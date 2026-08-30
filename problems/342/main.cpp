#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n);
    for(auto&v:x) scanf("%lld",&v);

    unordered_map<long long,int> last;
    last.reserve(n*2);
    long long ans=0;
    for(int i=0;i<n;i++){
        auto it=last.find(x[i]);
        int p = (it==last.end()) ? -1 : it->second;
        long long leftChoices = i - p;
        long long rightChoices = n - i;
        ans += leftChoices * rightChoices;
        last[x[i]] = i;
    }
    printf("%lld\n", ans);
}
