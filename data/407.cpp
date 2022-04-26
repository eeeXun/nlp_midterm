#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAXN 200000
#define START '+'
#define END '-'
#define TOKEN '#'
#define BASE 313
#define MOD1 998244353
#define MOD2 1000000009
#define ull unsigned long long
#define rint register int
#define gc() getchar()
inline int read(rint ans = 0, rint sgn = ' ', rint ch = gc())
{
	for(; ch < '0' || ch > '9'; sgn = ch, ch = gc());
	for(; ch >='0' && ch <='9';(ans*=10)+=ch-'0', ch = gc());
	return sgn-'-'?ans:-ans;
}
#define BUF_SIZE 1000000
#define _END fwrite(_Ob,1,_O-_Ob,stdout), _O = _Ob
#define Outc(a) (*_O++ = a)
char _Ob[BUF_SIZE+5], *_O = _Ob, _Os[25], *_Ot;
template <typename T> inline void Out(T x)
{
	if(!x){Outc('0'); return;} if(x < 0) Outc('-'), x = -x;
	for(_Ot = _Os; x; *_Ot++ = x%10+'0', x /= 10);
	for(; _Ot != _Os; Outc(*--_Ot)); if(_O-_Ob >= BUF_SIZE-50) _END;
}
char s[(MAXN>>1)+5], P[MAXN+5]; int o[MAXN+5], q[MAXN+5], n, N, C, lef, rig, mid, ans;
struct Seg{int L,R,K; Seg(){} Seg(int _L, int _R):L(_L),R(_R),K(_R-_L+1){}}M[MAXN+5], Ans[3];
inline bool operator < (Seg a, Seg b){return a.R<b.R;}
inline void Manacher()
{
	for(rint i = 1, id = 0, mx = o[0] = 1; i <= N; i+o[i] > mx ? mx = i+o[i], id = i : 0, i++)
		for(o[i] = mx <= i ?: min(o[(id<<1)-i],mx-i); P[i-o[i]] == P[i+o[i]]; ++o[i]); for(rint i = N; ~i; --o[i--]);
}
struct Hash
{
	ull h1,h2; Hash(){} Hash(ull _h1, ull _h2):h1(_h1),h2(_h2){}
	inline Hash operator + (Hash b){return Hash((h1+b.h1)%MOD1,(h2+b.h2)%MOD2);}
	inline Hash operator - (Hash b){return Hash((h1+MOD1-b.h1)%MOD1,(h2+MOD2-b.h2)%MOD2);}	
	inline Hash operator * (Hash b){return Hash(h1*b.h1%MOD1,h2*b.h2%MOD2);} 
	inline bool operator ==(Hash b){return h1 == b.h1 && h2 == b.h2;}
	inline bool operator !=(Hash b){return h1 != b.h1 && h2 != b.h2;}
}H[MAXN+5], R[MAXN+5], B[MAXN+5], tmp;
inline Hash Hv(int L, int _R){return H[_R]-H[L-1]*B[_R-L+1];}
inline Hash Rv(int L, int _R){return R[L]-R[_R+1]*B[_R-L+1];}
int main()
{
	scanf("%s",s+1), n = strlen(s+1), N = n<<1|1;
	B[0] = Hash(1,1), B[1] = Hash(BASE,BASE); for(rint i = 2; i <= n; B[i] = B[i-1]*B[1], i++);
	H[0] = Hash(0,0); for(rint i = 1; i <= n; H[i] = H[i-1]*B[1]+Hash(s[i],s[i]), i++);
	R[n+1] = Hash(0,0); for(rint i = n; i; R[i] = R[i+1]*B[1]+Hash(s[i],s[i]), i--);
	for(rint i = n; i; P[i<<1] = s[i], P[i<<1|1] = TOKEN, i--);
	P[0] = START, P[1] = TOKEN, P[N+1] = END; Manacher();
	for(rint i = 1; i <= N; o[i] ? M[++C] = Seg((i>>1)-(-~o[i]>>1)+1,(i>>1)+(-~o[i]>>1)-!(i&1)),0 : 0, i++);
	for(rint i = 1; i <= N; (M[i].K&1) && M[i].K > ans ? Ans[0] = M[i], ans = M[i].K : 0, i++);
	for(rint i = n, k = 1, l = 1, r = 1; i; q[i] = r, k++, i--)
		for(tmp = Rv(i,n); r <= n && Hv(l,r) != tmp; r++, l+= r-l>=k);
	for(rint i = C, K, J; i; i--)
		if(M[i].K&1)
		{
			for(lef = 1, rig = n-M[i].R+1; lef<rig; q[n-(mid=(lef+rig)>>1)+1]<M[i].L ? lef = mid+1 : rig = mid);
			if(K = rig-1, J = n-K+1, M[i].K+(K<<1) > ans)
				ans = M[i].K+(K<<1), Ans[0] = Seg(q[J]-K+1,q[J]), Ans[1] = M[i], Ans[2] = Seg(J,n);
		}
	C = 0; for(rint i = 0; i < 3; C += !!Ans[i].K, i++); printf("%d\n",C);
	for(rint i = 0; i < 3; Ans[i].K ? printf("%d %d\n",Ans[i].L,Ans[i].K) : 0, i++); return 0;
}
	  			 	   		 		 				   	   	