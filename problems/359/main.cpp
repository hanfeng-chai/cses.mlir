#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n+1), S(n+1,0);
    for(int i=1;i<=n;i++){ scanf("%lld",&x[i]); S[i]=S[i-1]+x[i]; }

    vector<long long> hx, hy; // lower hull of points (l-1, S[l-1])
    auto shouldPop=[&](long long px, long long py)->bool{
        int m=(int)hx.size();
        long long x1=hx[m-2], y1=hy[m-2];
        long long x2=hx[m-1], y2=hy[m-1];
        // slope(1,2) >= slope(1,new)  =>  point 2 is not below line(1,new): pop it
        return (y2-y1)*(px-x1) >= (py-y1)*(x2-x1);
    };

    string out; out.reserve(n*7);
    for(int i=1;i<=n;i++){
        long long px=i-1, py=S[i-1];
        while(hx.size()>=2 && shouldPop(px,py)){ hx.pop_back(); hy.pop_back(); }
        hx.push_back(px); hy.push_back(py);

        long long qx=i, qy=S[i];
        int lo=0, hi=(int)hx.size()-1;
        while(lo<hi){
            int mid=(lo+hi)/2;
            long long lhs=(qy-hy[mid])*(qx-hx[mid+1]);
            long long rhs=(qy-hy[mid+1])*(qx-hx[mid]);
            if(lhs<rhs) lo=mid+1; else hi=mid;
        }
        long long l = hx[lo]+1;
        out += to_string(i-l+1);
        out += (i==n) ? '\n' : ' ';
    }
    fputs(out.c_str(), stdout);
}
