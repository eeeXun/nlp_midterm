#include <bits/stdc++.h>
using namespace std;
#define rep(flag,a,b) for(int flag=(a);flag<=b;flag++) 
#define Rep(flag,a,b) for(int flag=(a);flag>=b;flag--) 
#define mem(flag) memset(flag,0,sizeof(flag))
#define Mem(flag) memset(flag,-1,sizeof(flag))
typedef long long ll;
const int MAX=2e5+7;
//#define DEBUG 

char s1[MAX],s[MAX];
int R[MAX]; int mine[MAX]; int b[MAX];

const int MAX2=22; //lg(MAX);
const int m=0xff+1;
int sa[MAX],x[MAX],y[MAX],c[MAX],rank[MAX],height[MAX];
int n;//the length of s,������һ��int���飬��ʵ������char�����ʾ�ı���;
//for RMQ
int maps[MAX][MAX2];
// m is the maxvalue of character(0~m-1);
void build_sa(int m) {
	rep(i,0,m-1) c[i]=0;
	rep(i,0,n-1) c[x[i]=s[i]]++;
	rep(i,1,m-1) c[i]+=c[i-1];
	Rep(i,n-1,0) sa[--c[x[i]]]=i;
	for(int k=1;k<=n;k<<=1) {
		int p=0;
		rep(i,n-k,n-1) y[p++]=i;
		rep(i,0,n-1) if(sa[i]>=k) y[p++]=sa[i]-k;
		rep(i,0,m-1) c[i]=0;
		rep(i,0,n-1) c[x[y[i]]]++;
		rep(i,1,m-1) c[i]+=c[i-1];
		Rep(i,n-1,0) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1,x[sa[0]]=0;
		rep(i,1,n-1) {
			x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&((sa[i-1]+k>=n&&sa[i]+k>=n)||(sa[i-1]+k<n&&sa[i]+k<n&&y[sa[i-1]+k]==y[sa[i]+k]))?
						p-1:p++;
		}
		if(p>=n) break;
		m=p;
	}
} 
void getHeight() {
	int i,j,k=0;
	#ifdef DEBUG
	for(i=0;i<n;i++) printf("%d ",sa[i]);
	printf("\n");
	#endif 
	for(i=0;i<n;i++) rank[sa[i]]=i;
	for(i=0;i<n;i++) {
		if(k!=0) k--;
		if(rank[i]==0) height[rank[i]]=0;
		else {
			int j=sa[rank[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rank[i]]=k;
		}
	}
}

void createSPTable(int M[][MAX2], int A[], int N)
{
    int i, j;
    for (i = 0; i < N; i++)
        M[i][0] = i;
    for (j = 1; 1 << j <= N; j++) {
        for (i = 0; i + (1 << j) - 1 < N; i++){
            if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
                M[i][j] = M[i][j - 1];
            else
                M[i][j] = M[i + (1 << (j - 1))][j - 1];
        }
    }
}

int spQuery(int i,int j,int M[][MAX2], int A[]) { //ret index
	int l=j-i+1,k=0;
	while(l>1) l>>=1,k++;
	if(A[M[i][k]]<=A[M[j+1-(1<<k)][k]]) return M[i][k];
	else return M[j+1-(1<<k)][k];
}


void manac(char *s,int *R) {
	int maxPos=-1,p=-1,len=strlen(s),l;
	for(int i=0;i<len;i++) {
		if(i>maxPos) {
			for(l=1;i+l<len&&i-l>=0&&s[i+l]==s[i-l];l++); 
			maxPos=max(maxPos,i+l-1);
			p=i; 
			R[i]=l-1;
		} else {
			int j=2*p-i,neMaxPos=2*p-maxPos;
			if(j-R[j]>neMaxPos) R[i]=R[j];
			else {
				for(l=1;maxPos+l<len&&2*i-maxPos-l>=0&&s[maxPos+l]==s[2*i-maxPos-l];l++);
				p=i;
				R[i]=maxPos+l-1-i;
				maxPos=max(maxPos,maxPos+l-1);
			}
		}
	}
}

struct xx{
	int pos;
	int k;
	int len;
	int l;
	int v;
} aa[MAX];
int nums=0;

int main() {
	#ifdef DEBUG
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int cases=4;
	while(cases--) {
	#endif
		nums=0;
		scanf("%s",s1);
		manac(s1,R);
		#ifdef DEBUG
		rep(i,0,strlen(s1)-1) {
			printf("pos=%d r=%d\n",i,R[i]);
		}
		#endif
		int len=strlen(s1);
		rep(i,0,len-1) {
			s[i]=s1[i];
		}
		s[len]='&';
		rep(i,len+1,2*len) {
			s[i]=s1[2*len-i];
		}
		s[2*len+1]='\0';
		n=strlen(s);
		#ifdef DEBUG
		printf("%s\n",s);
	#endif
		build_sa(m);
		getHeight();
		createSPTable(maps,height,n);
		rep(i,0,len-1) {
			int r1=rank[i],r2=rank[len+1];
			int idx=spQuery(min(r1,r2)+1,max(r1,r2),maps, height);
			mine[i]=height[idx];
		}
		Mem(b);
		int mm=INT_MIN;
		rep(i,0,len-1) {
			if(mm==INT_MIN) {
				mm=mine[i];
				rep(j,0,mm) {
					b[j]=0;
				}
			} else if(mine[i]>mm) {
				rep(j,mm+1,mine[i]) b[j]=i;
				mm=mine[i];
			}
		}
		#ifdef DEBUG
		rep(i,0,n-1) printf("%d ",height[i]);
		printf("\nmine:");
		rep(i,0,len-1) printf("%d ",mine[i]);
		printf("\nb");
		rep(i,0,len) printf("%d ",b[i]);
		printf("\n");
		#endif
		rep(i,0,len-1) {
			int pos=i,l=pos-R[i],r=pos+R[i];
			int msl=len-1-r;
			int low=0,high=msl,p;
			if(pos==2)
				p=1;
			while(low<=high) {
				#ifdef DEBUG
				printf("pos=%d low=%d high=%d\n",pos,low,high);
				#endif
				if(low==high) {
					if(b[low]+low-1<=l-1) break;
				}
				int mid=(low+high+1)>>1;
				if(b[mid]!=-1&&b[mid]+mid-1<=l-1) low=mid;
				else high=mid-1;
			}
			//find;
			if(low==0) {
				aa[nums].k=1;
				aa[nums].pos=pos;
				aa[nums].v=2*R[pos]+1;
				nums++;
			} else {
				aa[nums].pos=pos;
				aa[nums].k=3;
				aa[nums].len=low;
				aa[nums].l=b[low];
				aa[nums].v=2*R[pos]+1+aa[nums].len*2;
				nums++;
			}
		}
		int idd,opt=INT_MIN;
		for(int i=0;i<nums;i++) {
			if(aa[i].v>opt) {
				idd=i;
				opt=aa[i].v;
			}
		}
		if(aa[idd].k==1) {
			printf("1\n%d %d\n",aa[idd].pos-R[aa[idd].pos]+1,2*R[aa[idd].pos]+1);
		} else {
			printf("3\n%d %d\n%d %d\n%d %d\n",aa[idd].l+1,aa[idd].len,
			aa[idd].pos-R[aa[idd].pos]+1,2*R[aa[idd].pos]+1,
			len-aa[idd].len+1,aa[idd].len);
		}
	#ifdef DEBUG
	printf("\n\n");	
	}
	#endif
	return 0; 
}
