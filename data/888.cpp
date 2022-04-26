#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn=1e5+10;
const int inf=1e9+10;
const ll mod=1e9+7,p=47;

struct yxh{
	int lenth,mid_len,pre_len,pre_pos,suf_pos;
}ans[maxn];

ll step[maxn],hash1[maxn],hash2[maxn];
int n,c[maxn],len[maxn],pos[maxn];
string s;

int main(){
	cin>>s; n=(int)s.size();
	for(int i=0;i<n;i++) c[i]=s[i]-'a';
	step[0]=1;
	for(int i=1;i<maxn;i++) step[i]=step[i-1]*p%mod;
	hash1[0]=c[0]*step[n-1]%mod;
	for(int i=1;i<n;i++) hash1[i]=(c[i]*step[n-1-i]%mod+hash1[i-1])%mod;
	hash2[0]=c[0]*step[0]%mod;
	for(int i=1;i<n;i++) hash2[i]=(c[i]*step[i]%mod+hash2[i-1])%mod;
	for(int i=0;i<n;i++){
		int res=0,low=0,high=n+1-i;
		while(low<high){
			int mid=(low+high)>>1;
			if(i+mid-1<0){high=mid;continue;}
			ll hashval1=(hash1[i+mid-1]-(i>0?hash1[i-1]:0)+mod)%mod;
			ll hashval2=(hash2[n-1]-(n-mid>0?hash2[n-mid-1]:0)+mod)%mod;
			hashval1*=step[i]; hashval1%=mod;
			if(hashval1==hashval2) low=mid+1,res=max(res,mid);
			else high=mid;
		}
		len[i]=res;
	}
	for(int i=0;i<maxn;i++) pos[i]=inf;
	int plen=0;
	pos[0]=0;
	for(int i=0;i<n;i++) while(len[i]>plen) pos[++plen]=i;
	for(int i=0;i<n;i++){
		int res=0,low=0,high=n-i;
		while(low<high){
			int mid=(low+high)>>1;
			if(i-1<0){high=mid;continue;}
			if(i-mid<0){high=mid;continue;}
			ll hashval1=(hash1[i-1]-(i-mid>0?hash1[i-mid-1]:0)+mod)%mod;
			ll hashval2=(hash2[i+mid]-hash2[i]+mod)%mod;
			if(n-1<=2*i) hashval1*=step[2*i+1-n],hashval1%=mod;
			else hashval2*=step[n-1-2*i],hashval2%=mod;
			if(hashval1==hashval2) res=max(res,mid),low=mid+1;
			else high=mid;
		}
		int max_len=res;
		res=0,low=0,high=n-max_len-i;
		while(low<high){
			int mid=(low+high)>>1;
			if(pos[mid]+mid-1<i-max_len) res=max(res,mid),low=mid+1;
			else high=mid;
		}
		ans[i]=(yxh){max_len*2+res*2+1,max_len,res,pos[res],n-res};
	}
	int maxval=-inf,id=-1;
	for(int i=0;i<n;i++) if(maxval<ans[i].lenth) maxval=ans[i].lenth,id=i;
	printf("%d\n",ans[id].pre_len==0?1:3);
	if(ans[id].pre_len!=0) printf("%d %d\n",ans[id].pre_pos+1,ans[id].pre_len);
	printf("%d %d\n",id-ans[id].mid_len+1,ans[id].mid_len*2+1);
	if(ans[id].pre_len!=0) printf("%d %d\n",ans[id].suf_pos+1,ans[id].pre_len);
	return 0;
} 