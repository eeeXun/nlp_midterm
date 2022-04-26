template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 6 "data/961.cpp" 2


# 7 "data/961.cpp"
using namespace std;
# 18 "data/961.cpp"
inline int read(register int ans = 0, register int sgn = ' ', register int ch = getchar())
{
 for(; ch < '0' || ch > '9'; sgn = ch, ch = getchar());
 for(; ch >='0' && ch <='9';(ans*=10)+=ch-'0', ch = getchar());
 return sgn-'-'?ans:-ans;
}



char _Ob[1000000 +5], *_O = _Ob, _Os[25], *_Ot;
template <typename T> inline void Out(T x)
{
 if(!x){(*_O++ = '0'); return;} if(x < 0) (*_O++ = '-'), x = -x;
 for(_Ot = _Os; x; *_Ot++ = x%10+'0', x /= 10);
 for(; _Ot != _Os; (*_O++ = *--_Ot)); if(_O-_Ob >= 1000000 -50) fwrite(_Ob,1,_O-_Ob,
# 32 "data/961.cpp" 3 4
                                                           stdout
# 32 "data/961.cpp"
                                                           ), _O = _Ob;
}
char s[(200000>>1)+5], P[200000 +5]; int o[200000 +5], q[200000 +5], n, N, C, lef, rig, mid, ans;
struct Seg{int L,R,K; Seg(){} Seg(int _L, int _R):L(_L),R(_R),K(_R-_L+1){}}M[200000 +5], Ans[3];
inline bool operator < (Seg a, Seg b){return a.R<b.R;}
inline void Manacher()
{
 for(register int i = 1, id = 0, mx = o[0] = 1; i <= N; i+o[i] > mx ? mx = i+o[i], id = i : 0, i++)
  for(o[i] = mx <= i ?: min(o[(id<<1)-i],mx-i); P[i-o[i]] == P[i+o[i]]; ++o[i]); for(register int i = N; ~i; --o[i--]);
}
struct Hash
{
 unsigned long long h1,h2; Hash(){} Hash(unsigned long long _h1, unsigned long long _h2):h1(_h1),h2(_h2){}
 inline Hash operator + (Hash b){return Hash((h1+b.h1)%998244353,(h2+b.h2)%1000000009);}
 inline Hash operator - (Hash b){return Hash((h1+998244353 -b.h1)%998244353,(h2+1000000009 -b.h2)%1000000009);}
 inline Hash operator * (Hash b){return Hash(h1*b.h1%998244353,h2*b.h2%1000000009);}
 inline bool operator ==(Hash b){return h1 == b.h1 && h2 == b.h2;}
 inline bool operator !=(Hash b){return h1 != b.h1 && h2 != b.h2;}
}H[200000 +5], R[200000 +5], B[200000 +5], tmp;
inline Hash Hv(int L, int _R){return H[_R]-H[L-1]*B[_R-L+1];}
inline Hash Rv(int L, int _R){return R[L]-R[_R+1]*B[_R-L+1];}
int main()
{
 scanf("%s",s+1), n = strlen(s+1), N = n<<1|1;
 B[0] = Hash(1,1), B[1] = Hash(313,313); for(register int i = 2; i <= n; B[i] = B[i-1]*B[1], i++);
 H[0] = Hash(0,0); for(register int i = 1; i <= n; H[i] = H[i-1]*B[1]+Hash(s[i],s[i]), i++);
 R[n+1] = Hash(0,0); for(register int i = n; i; R[i] = R[i+1]*B[1]+Hash(s[i],s[i]), i--);
 for(register int i = n; i; P[i<<1] = s[i], P[i<<1|1] = '#', i--);
 P[0] = '+', P[1] = '#', P[N+1] = '-'; Manacher();
 for(register int i = 1; i <= N; o[i] ? M[++C] = Seg((i>>1)-(-~o[i]>>1)+1,(i>>1)+(-~o[i]>>1)-!(i&1)),0 : 0, i++);
 for(register int i = 1; i <= N; (M[i].K&1) && M[i].K > ans ? Ans[0] = M[i], ans = M[i].K : 0, i++);
 for(register int i = n, k = 1, l = 1, r = 1; i; q[i] = r, k++, i--)
  for(tmp = Rv(i,n); r <= n && Hv(l,r) != tmp; r++, l+= r-l>=k);
 for(register int i = C, K, J; i; i--)
  if(M[i].K&1)
  {
   for(lef = 1, rig = n-M[i].R+1; lef<rig; q[n-(mid=(lef+rig)>>1)+1]<M[i].L ? lef = mid+1 : rig = mid);
   if(K = rig-1, J = n-K+1, M[i].K+(K<<1) > ans)
    ans = M[i].K+(K<<1), Ans[0] = Seg(q[J]-K+1,q[J]), Ans[1] = M[i], Ans[2] = Seg(J,n);
  }
 C = 0; for(register int i = 0; i < 3; C += !!Ans[i].K, i++); printf("%d\n",C);
 for(register int i = 0; i < 3; Ans[i].K ? printf("%d %d\n",Ans[i].L,Ans[i].K) : 0, i++); return 0;
}
