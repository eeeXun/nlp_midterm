      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 4 "data/111.cpp" 2

# 4 "data/111.cpp"
using namespace std;
# 17 "data/111.cpp"
long long int power[1000001],pre[1000001],suff[1000001],base=127,dp[1000001];
long long int getpre(long long int l,long long int r)
{
 return pre[r]-pre[l-1]*power[r-l+1];
}
long long int getsuff(long long int l,long long int r)
{
 return suff[l]-suff[r+1]*power[r-l+1];
}
int main()
{
 ios::sync_with_stdio(false);;cin.tie(0);;
 string s;
 long long int i,j,k,l,lo,mid,hi,x1,x2,x3,l1,l2,l3,x,y,ans=0;
 cin>>s;
 l=s.length();
 pre[0]=s[0]-'a';
 for(i=1;i<l;i++)
 pre[i]=pre[i-1]*base+s[i]-'a';
 suff[l-1]=s[l-1]-'a';
 for(i=l-2;i>=0;i--)
 suff[i]=suff[i+1]*base+s[i]-'a';
 power[0]=1;
 for(i=1;i<=l;i++)
 power[i]=base*power[i-1];
 for(i=0;i<=l;i++)
 dp[i]=100000000;
 for(i=0;i<l;i++)
 {
  lo=0;
  hi=(l-i)/2;
  while(lo<hi)
  {
   mid=(lo+hi+1)/2;
   if(getpre(i,i+mid-1)==getsuff(l-mid,l-1))
   lo=mid;
   else
   hi=mid-1;
  }
  dp[lo]=min(dp[lo],i);
 }
 for(i=l;i>=0;i--)
 {
  dp[i-1]=min(dp[i-1],dp[i]);
  dp[i]+=i-1;
 }
 for(i=0;i<l;i++)
 {
  lo=0;
  hi=min(i,l-i-1);
  while(lo<hi)
  {
   mid=(lo+hi+1)/2;
   if(getpre(i-mid,i)==getsuff(i,i+mid))
   lo=mid;
   else
   hi=mid-1;
  }
  x=lo;
  lo=0;
  hi=l-x-1-i;
  while(lo<hi)
  {
   mid=(lo+hi+1)/2;
   if(dp[mid]+x<i)
   lo=mid;
   else
   hi=mid-1;
  }
  if(2*x+1+2*lo>ans)
  {
   ans=2*x+1+2*lo;
   x1=dp[lo]-lo+1;
   x2=i-x;
   x3=l-lo;
   l1=lo;
   l3=lo;
   l2=2*x+1;
  }
 }
 if(l1)
 {
  cout<<"3"<<endl;
  cout<<x1+1<<" "<<l1<<endl;
  cout<<x2+1<<" "<<l2<<endl;
  cout<<x3+1<<" "<<l3<<endl;
 }
 else
 {
  cout<<"1"<<endl;
  cout<<x2+1<<" "<<l2<<endl;
 }
 return 0;
}
