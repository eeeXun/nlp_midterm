#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <cmath>
#include <cctype>
using namespace std;
#define FOR(i,s,e) for(int i=(s);i<(int)(e);i++)
#define FOE(i,s,e) for(int i=(s);i<=(int)(e);i++)
#define CLR(s) memset(s,0,sizeof(s))
typedef long long LL;

const int INF = 1<<28;
const int M = 210010;
int *SA,*SA2,*R,*R2;
int _SA[M],_SA2[M],_R[M],_R2[M],cnt[M],h[M];

bool valid(char c){ return c!='#'; }

void SuffixArray(char *s,int n){
        SA=_SA; SA2=_SA2; R=_R; R2=_R2;
        CLR(cnt);
        FOR(i,0,n) ++cnt[s[i]];
        FOR(j,1,256) cnt[j]+=cnt[j-1];
        FOR(i,0,n) SA[--cnt[s[i]]]=i;
        R[SA[0]]=0;
        FOR(i,0,n) R[SA[i]]=R[SA[i-1]]+(s[SA[i]]!=s[SA[i-1]]);
        for (int k=1; k<=n; k<<=1){
                FOR(i,0,n) cnt[R[SA[i]]]=i+1;
                for (int i=n-1; i>=0; i--){
                        if (SA[i]>=k) SA2[--cnt[R[SA[i]-k]]]=SA[i]-k;
                }
                FOR(i,n-k,n) SA2[--cnt[R[i]]]=i;
                R2[SA2[0]]=0;
                FOR(i,1,n){
                        R2[SA2[i]]=R2[SA2[i-1]];
                        if (R[SA2[i]]!=R[SA2[i-1]]) R2[SA2[i]]++;
                        else if (SA2[i]+k < n && SA2[i-1]+k>=n) R2[SA2[i]]++;
                        else if (SA2[i]+k<n && SA2[i-1]+k<n && R[SA2[i]+k]!=R[SA2[i-1]+k])
                                R2[SA2[i]]++;
                }
                swap(R,R2); swap(SA,SA2);
        }
        CLR(h);
        for (int i=0,k=0; i<n; i++){
                if (R[i]==n-1){ h[i]=0; continue; }
                if (k>0) --k;
                int j=SA[R[i]+1];
                while (i+k<n && j+k<n && s[i+k]==s[j+k] && valid(s[i+k])) k++;
                h[i]=k;
        }
//      FOR(i,0,n)      printf("[%3d] %s\n", h[SA[i]], s+SA[i]);
}

char s[M];
int n, m;
int ST[19][M];
int len[M];
int ID[19][M];

int max_rev(int i) {    // Span from the middle of i-1,i
        if (i<0) return -1;
        int st=R[i], ed=R[2*n-i];
        if (st>ed) swap(st,ed);
//      puts(s+SA[st]);
//      puts(s+SA[ed]);
        int k=0;
        while ((1<<k)*2<=ed-st) ++k;
        return min(ST[k][st], ST[k][ed-(1<<k)]);
}

int pre[M];     // pre[i] := earliest pos of prefix with leng=i

void query(int st, int ed, int &len, int &idx) {
//      st=22,ed=24;
        int k=0;
        while ((1<<k)*2<=ed-st) ++k;
        len=ST[k][st];
        idx=ID[k][st];
        if (ST[k][ed-(1<<k)]>len) {
                len=ST[k][ed-(1<<k)];
                idx=ID[k][ed-(1<<k)];
        }
//      printf("[%d %d] %d %d k=%d\n", st, ed, len, idx, k);
}

int main() {
        scanf("%s",s);
        n = strlen(s);
        m = n;
        s[m++] = '#';
        for (int i=n-1; i>=0; i--) s[m++] = s[i];
        s[m] = 0;

        SuffixArray(s, m);
        FOR(i,0,m) ST[0][i]=h[SA[i]];
        for(int j=1,k=2;k<=m;j++,k*=2) {
                for(int i=0;i+k<=m;i++) {
                        ST[j][i]=min(ST[j-1][i], ST[j-1][i+k/2]);
                }
        }

        FOR(i,0,n) len[i]=max_rev(i)*2-1;
        // Build Sparse Table for "len"
        FOR(i,0,n) {
                ST[0][i]=len[i];
                ID[0][i]=i;
//              printf("[%3d] %d\n", i, len[i]);
        }
        for(int j=1,k=2;k<=n;j++,k*=2) {
                for(int i=0;i+k<=n;i++) {
                        ST[j][i]=ST[j-1][i];
                        ID[j][i]=ID[j-1][i];
                        if (ST[j-1][i+k/2] > ST[j-1][i]) {
                                ST[j][i]=ST[j-1][i+k/2];
                                ID[j][i]=ID[j-1][i+k/2];
                        }
//                      if (ID[j][i] < i || ID[j][i] >= i+k) printf("[%d %d] %d\n", i, i+k ,ID[j][i]);
                }
        }

        // TODO: ST for len[]
        FOE(i,0,n) pre[i]=INF;
        int pos=R[n+1];
//      printf("s=%s\n", s+n+1);
//      printf("R=%d\n", R[n+1]);
        // roll down SA..
//      puts("DOWN");
        for(int pos=R[n+1], len=INF; pos+1<m; pos++) {
                len=min(len, h[SA[pos]]);
                int idx=SA[pos+1];
//              printf("len=%d pos=%d\n", len, idx);
                pre[len]=min(pre[len], idx);
        }
//      puts("UP");
        for(int pos=R[n+1], len=INF; pos-1>=0; pos--) {
                len=min(len, h[SA[pos-1]]);
                int idx=SA[pos-1];
//              printf("len=%d pos=%d\n", len, idx);
                pre[len]=min(pre[len], idx);
        }
/*
        FOE(i,0,n) if(pre[i]!=INF) {
                printf("len[%2d]=%2d %s\n", i, pre[i], s+pre[i]);
        }
*/
        for(int i=n-1;i>=0;i--) {
                pre[i]=min(pre[i], pre[i+1]);
        }

        int lo=0, hi=n+1;
        int len0, idx0; // prefix
        int len1, idx1; // middle
        int len2, idx2;
        int ans=-1;
        while (lo+1<hi) {
                int md=lo+hi>>1;
                bool fd=0;
//              printf("[%d,%d) md=%d\n", lo, hi, md);
                FOE(i,0,n) if(!fd) {
                        int wat=md-2*i;
                        int half=(md-2*i)/2;
                        int idx, len;
                        if (pre[i]+i >= n-i) break;
//                      printf("[%d %d]\n", pre[i]+i+half, n-i-half);
                        query(pre[i]+i+half, n-i-half, len, idx);
//                      printf("%d\n", len);
                        if(len>=2*half+1) {
                                fd=1;
                                if(md>ans && md%2==1) {
//                                      printf("\nlen=%d udx-%d\n", len, idx);
//                                      printf("half=%d\n", half);
//                                      printf("Query [%d ,%d]\n", pre[i]+i+half, n-i-half);
                                        ans=md;
                                        len0=i;
                                        idx0=pre[i];
                                        idx1=idx-half;
                                        len1=md-2*i;
                                        len2=i;
                                        idx2=n-i;
//                                      printf("md=%d\n", md);
//                                      printf("%d %d\n%d %d\n%d %d\n", idx0,len0,idx1,len1,idx2,len2);
                                }
                        }
                }
                (fd ? lo : hi) = md;
        }
        if (len0==0) {
                printf("1\n%d %d\n", idx1+1, len1);
        } else {
                printf("3\n");
                printf("%d %d\n", idx0+1, len0);
                printf("%d %d\n", idx1+1, len1);
                printf("%d %d\n", idx2+1, len2);
        }
        return 0;
}
