# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 5 "data/374.cpp" 2


# 6 "data/374.cpp"
using namespace std;

enum {MAXN = 100010,MAXT = MAXN * 2};
typedef pair<int,int> pii;
char s[MAXN],rs[MAXN];
int mlen[MAXN];

void solveMlen(const char *s)
{
  int len = strlen(s);
  int maxp,maxr = 0;
  for(int i = 0;i < len;i++)
    {
      if (i < maxr) mlen[i] = min(mlen[2 * maxp - i],maxr - i);
      else mlen[i] = 1;
      for(;i + mlen[i] < len && i - mlen[i] >= 0 && s[i + mlen[i]] == s[i - mlen[i]];mlen[i]++);

      if (i + mlen[i] > maxr)
 {
   maxp = i;
   maxr = i + mlen[i];
 }
    }
}



int minlb[MAXT],maxrb[MAXT];
pii maxl[MAXT];

void build(int l,int r)
{
  if (l < r)
    {
      int mid = (l + r) >> 1;
      build(l,mid);
      build(mid + 1,r);
      minlb[(((l) + (r)) | ((l) != (r)))] = min(minlb[(((l) + (mid)) | ((l) != (mid)))],minlb[(((mid + 1) + (r)) | ((mid + 1) != (r)))]);
      maxrb[(((l) + (r)) | ((l) != (r)))] = max(maxrb[(((l) + (mid)) | ((l) != (mid)))],maxrb[(((mid + 1) + (r)) | ((mid + 1) != (r)))]);
      maxl[(((l) + (r)) | ((l) != (r)))] = max(maxl[(((l) + (mid)) | ((l) != (mid)))],maxl[(((mid + 1) + (r)) | ((mid + 1) != (r)))]);
    }
  else
    {
      minlb[(((l) + (r)) | ((l) != (r)))] = l - mlen[l];
      maxrb[(((l) + (r)) | ((l) != (r)))] = l + mlen[l];
      maxl[(((l) + (r)) | ((l) != (r)))] = pii(mlen[l],l);
    }
}

pii findMaxl(int l,int r,int s,int e)
{
  if (s > e) return pii(0,0);
  if (s <= l && r <= e) return maxl[(((l) + (r)) | ((l) != (r)))];
  else
    {
      int mid = (l + r) >> 1;
      return max(s <= mid ? findMaxl(l,mid,s,e) : pii(0,0),e > mid ? findMaxl(mid + 1,r,s,e) : pii(0,0));
    }
}

int findLstLb(int l,int r,int s,int e)
{
  if (minlb[(((l) + (r)) | ((l) != (r)))] >= s || s > e) return s-1;
  else
    {
      if (s <= l && r <= e)
 {
   int mid;
   while(l < r)
     {
       mid = (l + r) >> 1;
       if (minlb[(((mid + 1) + (r)) | ((mid + 1) != (r)))] < s) l = mid + 1;
       else r = mid;
     }
   return l;
 }
      else
 {
   int mid = (l + r) >> 1,res = s-1;
   if (e > mid) res = findLstLb(mid + 1,r,s,e);
   return res == s-1 && s <= mid ? findLstLb(l,mid,s,e) : res;
 }
    }
}

int findFstRb(int l,int r,int s,int e)
{
  if (maxrb[(((l) + (r)) | ((l) != (r)))] <= e || s > e) return e+1;
  else
    {
      if (s <= l && r <= e)
 {
   int mid;
   while(l < r)
     {
       mid = (l + r) >> 1;
       if (maxrb[(((l) + (mid)) | ((l) != (mid)))] > e) r = mid;
       else l = mid + 1;
     }
   return l;
 }
      else
 {
   int mid = (l + r) >> 1,res = e+1;
   if (s <= mid) res = findFstRb(l,mid,s,e);
   return res == e+1 && e > mid ? findFstRb(mid + 1,r,s,e) : res;
 }
    }
}

pii queryRange(int n,int l,int r)
{
  int mid = (l + r) >> 1;
  int lb = findLstLb(0,n - 1,l,mid);
  int rb = findFstRb(0,n - 1,mid + 1,r);
  return max(findMaxl(0,n - 1,lb + 1,rb - 1),max(pii(lb - l + 1,lb),pii(r - rb + 1,rb)));
}

int nxt[MAXN],match[MAXN],mpos[MAXN];

void getNxt(const char *t)
{
  int len = strlen(t),i,j;
  nxt[0] = -1;
  for(i = 1,j = 0;i < len;)
    {
      if (t[i] == t[j]) nxt[i] = nxt[j];
      else nxt[i] = j;

      for(;j != -1 && t[i] != t[j];j = nxt[j]);
      i++,j++;
    }
  nxt[len] = j;
}

void kmpMatch(const char *s,const char *t,int *match)
{
  getNxt(t);
  int slen = strlen(s),tlen = strlen(t);
  for(int i = 0,j = 0;i < slen;i++)
    {
      for(;j != -1 && s[i] != t[j];j = nxt[j]);
      match[i] = ++j;
      if (j == tlen) j = nxt[j];
    }
}

int main()
{
  scanf("%s",s);
  int n = strlen(s);
  solveMlen(s);
  build(0,n - 1);

  copy(s,s + n,rs);
  reverse(rs,rs + n);
  kmpMatch(s,rs,match);

  for(int i = 0;i <= n;i++) mpos[i] = n;
  for(int i = n - 1;i >= 0;i--) mpos[match[i]] = i;

  int ans1 = 0;
  pii ta,tb,tc;
  for(int i = 1;i <= n && mpos[i] + 1 <= n - i - 1;i++)
    {
      pii res = queryRange(n,mpos[i] + 1,n - i - 1);
      if (res.first * 2 + i * 2 - 1 > ans1)
 {
   ans1 = res.first * 2 + i * 2 - 1;
   ta = pii(mpos[i] - i + 1,i);
   tb = pii(res.second - res.first + 1,res.first * 2 - 1);
   tc = pii(n - i,i);
 }
    }

  pii ans2 = queryRange(n,0,n - 1);

  if (ans1 > ans2.first * 2 - 1)
    {
      puts("3");
      printf("%d %d\n",ta.first + 1,ta.second);
      printf("%d %d\n",tb.first + 1,tb.second);
      printf("%d %d\n",tc.first + 1,tc.second);
    }
  else
    {
      puts("1");
      printf("%d %d\n",ans2.second - ans2.first + 2,ans2.first * 2 - 1);
    }
  return 0;
}
