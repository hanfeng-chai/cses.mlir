#include <bits/stdc++.h>
using namespace std;

long long gcdll(long long a,long long b){ while(b){ a%=b; swap(a,b); } return a; }

long long countInRange(long long N, long long M, long long rem){
    if(N<=0) return 0;
    rem %= M;
    if(rem==0) return N/M;
    if(rem>N) return 0;
    return (N-rem)/M + 1;
}

// count (r,c) in [1,A]x[1,B] with r == c (mod M)
long long countSameResidue(long long A, long long B, long long M){
    if(A<=0 || B<=0) return 0;
    long long cost1=M, cost2=(A+B)/M+3;
    long long total=0;
    if(cost1<=cost2){
        for(long long rem=0; rem<M; rem++)
            total += countInRange(A,M,rem)*countInRange(B,M,rem);
    } else {
        long long tmin=-(B/M)-2, tmax=(A/M)+2;
        for(long long t=tmin;t<=tmax;t++){
            long long lo=max(1LL, t*M+1), hi=min(A, t*M+B);
            if(hi>=lo) total += hi-lo+1;
        }
    }
    return total;
}

// count (r,c) in [1,A]x[1,B] with r+c == 0 (mod M)
long long countNegResidue(long long A, long long B, long long M){
    if(A<=0 || B<=0) return 0;
    long long cost1=M, cost2=(A+B)/M+3;
    long long total=0;
    if(cost1<=cost2){
        for(long long rem=0; rem<M; rem++){
            long long rem2=(M-rem)%M;
            total += countInRange(A,M,rem)*countInRange(B,M,rem2);
        }
    } else {
        long long smin=-2, smax=(A+B)/M+2;
        for(long long s=smin;s<=smax;s++){
            long long lo=max(1LL, s*M-B), hi=min(A, s*M-1);
            if(hi>=lo) total += hi-lo+1;
        }
    }
    return total;
}

// fix one coordinate = u in {0, a}; count total DISTINCT values of the OTHER coordinate
// (b = the other dimension's length, g = gcd), including its own boundary values 0/b.
long long boundaryTotalCount(long long u, long long b, long long g){
    long long tg=2*g;
    long long ru = u % tg;
    long long bp = b/g;
    long long w0 = ru/g; // 0 or 1
    if(w0==0) return 1 + bp/2;
    else return (bp+1)/2;
}

int main(){
    int t; scanf("%d",&t);
    string out;
    for(int i=0;i<t;i++){
        long long n,m; scanf("%lld %lld",&n,&m);
        long long a=n-1, b=m-1;
        long long g=gcdll(a,b);
        long long period = 2*(a/g)*b; // 2*lcm(a,b)

        long long M=2*g, A=a-1, B=b-1;
        long long NA=countSameResidue(A,B,M);
        long long NB=countNegResidue(A,B,M);
        long long NAB = countInRange(A,M,0)*countInRange(B,M,0);
        if(M%2==0) NAB += countInRange(A,M,M/2)*countInRange(B,M,M/2);
        long long interior = NA+NB-NAB;

        long long tg=2*g;
        long long cols_r0 = boundaryTotalCount(0,b,g);
        long long cols_ra = boundaryTotalCount(a,b,g);
        long long rows_total_c0 = boundaryTotalCount(0,a,g);
        long long rows_total_cb = boundaryTotalCount(b,a,g);
        bool ra_in_c0 = (0%tg)==(a%tg);
        bool r0_in_cb = (b%tg)==(0%tg);
        bool ra_in_cb = (b%tg)==(a%tg);
        long long rows_c0_interior = rows_total_c0 - 1 - (ra_in_c0?1:0);
        long long rows_cb_interior = rows_total_cb - (r0_in_cb?1:0) - (ra_in_cb?1:0);

        long long distinct = interior + cols_r0 + cols_ra + rows_c0_interior + rows_cb_interior;

        out += to_string(period); out+=' ';
        out += to_string(distinct); out+='\n';
    }
    fputs(out.c_str(), stdout);
}

