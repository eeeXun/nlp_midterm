}
# 9 "data/569.cpp" 2
# 1 "/usr/include/c++/11.2.0/cctype" 1 3
# 39 "/usr/include/c++/11.2.0/cctype" 3
       
# 40 "/usr/include/c++/11.2.0/cctype" 3
# 10 "data/569.cpp" 2

# 10 "data/569.cpp"
using namespace std;



typedef long long LL;

const int INF = 1<<28;
const int M = 210010;
int *SA,*SA2,*R,*R2;
int _SA[M],_SA2[M],_R[M],_R2[M],cnt[M],h[M];

bool valid(char c){ return c!='#'; }

void SuffixArray(char *s,int n){
        SA=_SA; SA2=_SA2; R=_R; R2=_R2;
        memset(cnt,0,sizeof(cnt));
        for(int i=(0);i<(int)(n);i++) ++cnt[s[i]];
        for(int j=(1);j<(int)(256);j++) cnt[j]+=cnt[j-1];
        for(int i=(0);i<(int)(n);i++) SA[--cnt[s[i]]]=i;
        R[SA[0]]=0;
        for(int i=(0);i<(int)(n);i++) R[SA[i]]=R[SA[i-1]]+(s[SA[i]]!=s[SA[i-1]]);
        for (int k=1; k<=n; k<<=1){
                for(int i=(0);i<(int)(n);i++) cnt[R[SA[i]]]=i+1;
                for (int i=n-1; i>=0; i--){
                        if (SA[i]>=k) SA2[--cnt[R[SA[i]-k]]]=SA[i]-k;
                }
                for(int i=(n-k);i<(int)(n);i++) SA2[--cnt[R[i]]]=i;
                R2[SA2[0]]=0;
                for(int i=(1);i<(int)(n);i++){
                        R2[SA2[i]]=R2[SA2[i-1]];
                        if (R[SA2[i]]!=R[SA2[i-1]]) R2[SA2[i]]++;
                        else if (SA2[i]+k < n && SA2[i-1]+k>=n) R2[SA2[i]]++;
                        else if (SA2[i]+k<n && SA2[i-1]+k<n && R[SA2[i]+k]!=R[SA2[i-1]+k])
                                R2[SA2[i]]++;
                }
                swap(R,R2); swap(SA,SA2);
        }
        memset(h,0,sizeof(h));
        for (int i=0,k=0; i<n; i++){
                if (R[i]==n-1){ h[i]=0; continue; }
                if (k>0) --k;
                int j=SA[R[i]+1];
                while (i+k<n && j+k<n && s[i+k]==s[j+k] && valid(s[i+k])) k++;
                h[i]=k;
        }

}

char s[M];
int n, m;
int ST[19][M];
int len[M];
int ID[19][M];

int max_rev(int i) {
        if (i<0) return -1;
        int st=R[i], ed=R[2*n-i];
        if (st>ed) swap(st,ed);


        int k=0;
        while ((1<<k)*2<=ed-st) ++k;
        return min(ST[k][st], ST[k][ed-(1<<k)]);
}

int pre[M];

void query(int st, int ed, int &len, int &idx) {

        int k=0;
        while ((1<<k)*2<=ed-st) ++k;
        len=ST[k][st];
        idx=ID[k][st];
        if (ST[k][ed-(1<<k)]>len) {
                len=ST[k][ed-(1<<k)];
                idx=ID[k][ed-(1<<k)];
        }

}

int main() {
        scanf("%s",s);
        n = strlen(s);
        m = n;
        s[m++] = '#';
        for (int i=n-1; i>=0; i--) s[m++] = s[i];
        s[m] = 0;

        SuffixArray(s, m);
        for(int i=(0);i<(int)(m);i++) ST[0][i]=h[SA[i]];
        for(int j=1,k=2;k<=m;j++,k*=2) {
                for(int i=0;i+k<=m;i++) {
                        ST[j][i]=min(ST[j-1][i], ST[j-1][i+k/2]);
                }
        }

        for(int i=(0);i<(int)(n);i++) len[i]=max_rev(i)*2-1;

        for(int i=(0);i<(int)(n);i++) {
                ST[0][i]=len[i];
                ID[0][i]=i;

        }
        for(int j=1,k=2;k<=n;j++,k*=2) {
                for(int i=0;i+k<=n;i++) {
                        ST[j][i]=ST[j-1][i];
                        ID[j][i]=ID[j-1][i];
                        if (ST[j-1][i+k/2] > ST[j-1][i]) {
                                ST[j][i]=ST[j-1][i+k/2];
                                ID[j][i]=ID[j-1][i+k/2];
                        }

                }
        }


        for(int i=(0);i<=(int)(n);i++) pre[i]=INF;
        int pos=R[n+1];




        for(int pos=R[n+1], len=INF; pos+1<m; pos++) {
                len=min(len, h[SA[pos]]);
                int idx=SA[pos+1];

                pre[len]=min(pre[len], idx);
        }

        for(int pos=R[n+1], len=INF; pos-1>=0; pos--) {
                len=min(len, h[SA[pos-1]]);
                int idx=SA[pos-1];

                pre[len]=min(pre[len], idx);
        }





        for(int i=n-1;i>=0;i--) {
                pre[i]=min(pre[i], pre[i+1]);
        }

        int lo=0, hi=n+1;
        int len0, idx0;
        int len1, idx1;
        int len2, idx2;
        int ans=-1;
        while (lo+1<hi) {
                int md=lo+hi>>1;
                bool fd=0;

                for(int i=(0);i<=(int)(n);i++) if(!fd) {
                        int wat=md-2*i;
                        int half=(md-2*i)/2;
                        int idx, len;
                        if (pre[i]+i >= n-i) break;

                        query(pre[i]+i+half, n-i-half, len, idx);

                        if(len>=2*half+1) {
                                fd=1;
                                if(md>ans && md%2==1) {



                                        ans=md;
                                        len0=i;
                                        idx0=pre[i];
                                        idx1=idx-half;
                                        len1=md-2*i;
                                        len2=i;
                                        idx2=n-i;


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
