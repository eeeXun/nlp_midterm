  extern template class basic_ostringstream<wchar_t>;
  extern template class basic_stringstream<wchar_t>;




}
# 1218 "/usr/include/c++/11.2.0/sstream" 2 3
# 15 "data/708.cpp" 2
# 1 "/usr/include/c++/11.2.0/ctime" 1 3
# 39 "/usr/include/c++/11.2.0/ctime" 3
       
# 40 "/usr/include/c++/11.2.0/ctime" 3
# 58 "/usr/include/c++/11.2.0/ctime" 3
namespace std
{
  using ::clock_t;
  using ::time_t;
  using ::tm;

  using ::clock;
  using ::difftime;
  using ::mktime;
  using ::time;
  using ::asctime;
  using ::ctime;
  using ::gmtime;
  using ::localtime;
  using ::strftime;
}



namespace std
{
  using ::timespec;
  using ::timespec_get;
}
# 16 "data/708.cpp" 2

# 16 "data/708.cpp"
using namespace std;

#pragma comment(linker,"/STACK:1608864")



typedef vector<pair<int, int> > vec;


void ASS(bool b){if (!b)++*(int*)0;}




typedef long long LL;
typedef vector<int> vi;

const int N = 1 << 17;

struct chash
{
 LL p[N];
 LL a[N];
 void Init(char *s, int n)
 {
  a[0] = 0;
  p[0] = 1;
  for (int i = 0; i < (int)(n); i++)
  {
   p[i + 1] = p[i] * 2999;
   a[i + 1] = a[i] * 2999 + s[i] - 'a' + 1;
  }
 }
 LL hash(int pos, int k)
 {
  return a[pos + k] - a[pos] * p[k];
 }
};

int n;


chash h0, h1;

int MaxX(int pos)
{
 int L = 0;
 int R = (n - pos) / 2;
 while (pos + R * 2 >= n) R--;
 R++;
 while (R - L > 1)
 {
  int m = (L + R) >> 1;
  if (h0.hash(pos, m) == h1.hash(0, m))
   L = m;
  else
   R = m;
 }
 return L;
}

struct RSQ
{
 int a[N * 2];
 int p[N * 2];
 void Init(int v)
 {
  if (v >= N) return;
  Init(v * 2);
  Init(v * 2 + 1);
  if (a[v * 2] > a[v * 2 + 1])
  {
   a[v] = a[v * 2];
   p[v] = p[v * 2];
  }
  else
  {
   a[v] = a[v * 2 + 1];
   p[v] = p[v * 2 + 1];
  }
 }
 int Max(int L, int R)
 {
  int res = 0;
  for (L += N, R += N; L < R; L >>= 1, R >>= 1)
  {
   if (L & 1)
   {
    res = max(res, a[L]);
    L++;
   }
   if (R & 1)
   {
    R--;
    res = max(res, a[R]);
   }
  }
  return res;
 }
 int MaxP(int L, int R)
 {
  int Max = -1, pos = -1;
  for (L += N, R += N; L < R; L >>= 1, R >>= 1)
  {
   if (L & 1)
   {
    if (Max < a[L])
    {
     Max = a[L];
     pos = p[L];
    }
    L++;
   }
   if (R & 1)
   {
    R--;
    if (Max < a[R])
    {
     Max = a[R];
     pos = p[R];
    }
   }
  }
  ASS(pos >= 0);
  return pos;
 }
};

RSQ rsq;

char s[N];

vector<pair<int, int> > Solve(string Str)
{
 memset(rsq.a,0,sizeof(rsq.a));

 strcpy(s, Str.c_str());
 n = (int)strlen(s);
 h0.Init(s, n);
 reverse(s, s + n);
 h1.Init(s, n);
 reverse(s, s + n);
 for (int i = 0; i < (int)(n); i++)
 {
  int L = 0;
  int R = min(i, n - 1 - i);
  R++;
  while (R - L > 1)
  {
   int m = (L + R) >> 1;
   if (h0.hash(i, m + 1) == h1.hash(n - 1 - i, m + 1))
    L = m;
   else
    R = m;
  }
  rsq.a[N + i] = L;
  rsq.p[N + i] = i;

 }
 rsq.Init(1);
 int BestLen = 1, BestX = 0;
 int p0 = 0;
 int p1 = 0;
 int p2 = 0;
 for (int i = 0; i < (int)(n - 1); i++)
 {
  if (s[i] != s[n - 1]) continue;
  int x = MaxX(i);
  int L = 0;
  int R = (n - i - 2 * x) / 2;
  ASS(R >= 0);
  R += 2;
  while (R - L > 1)
  {
   int m = (L + R) >> 1;
   if (rsq.Max(i + x + m, n - x - m) >= m)
    L = m;
   else
    R = m;

  }
  if (BestLen < x * 2 + L * 2 + 1)
  {
   BestLen = x * 2 + L * 2 + 1;
   BestX = x;
   p0 = i;
   p1 = rsq.MaxP(i + x + L, n - x - L) - L;
   p2 = n - x;
  }
 }

 string str(s);

 for (int i = 0; i < (int)(n); i++)
 {
  int d = rsq.a[N + i];
  if (BestLen < d * 2 + 1)
  {
   BestLen = d * 2 + 1;
   BestX = 0;
   p0 = i - d;
  }
 }
# 227 "data/708.cpp"
 vector<pair<int, int> > Ans;
 Ans.push_back(make_pair(p0 + 1, BestLen));

 ASS(BestLen & 1);

 if (BestX)
 {
  string s0 = str.substr(p0, BestX);
  string s1 = str.substr(p1, BestLen - 2 * BestX);
  string s2 = str.substr(p2, BestX);
  string ss0 = s0 + s1 + s2;
  string ss1 = ss0;
  reverse(ss1.begin(), ss1.end());
  ASS(ss0 == ss1);
  ASS(BestLen <= n);
  ASS(p0 >= 0 && p0 < n);
  ASS(p1 >= 0 && p1 < n);
  ASS(p2 >= 0 && p2 + BestX <= n);
  ASS(p0 + BestX <= p1);
  ASS(p1 + BestLen - 2 * BestX <= p2);




  Ans.clear();
  Ans.push_back(make_pair(p0 + 1, BestX));
  Ans.push_back(make_pair(p1 + 1, BestLen - 2 * BestX));
  Ans.push_back(make_pair(p2 + 1, BestX));
  return Ans;
 }
 return Ans;
}

bool IsPal(string s)
{
 for (int i = 0; i < (int)(s.size()); i++)
  if (s[i] != s[s.size() - 1 - i])
   return 0;
 return 1;
}

vector<pair<int, int> > SolveV(string s)
{
    int BestLen = 0;
    vector<pair<int, int> > res;
    for (int i = 0; i < s.length(); ++i)
        for(int j = i; j < s.length(); ++j)
            if (IsPal(s.substr(i, j - i + 1)) && j - i + 1 > BestLen && (j - i + 1) % 2 == 1)
            {
                    BestLen = j - i + 1;
                    res.clear();
                    res.push_back(make_pair(i + 1, BestLen));
                    break;
            }
 for (int i = 0; i < s.size(); i++)
 {
  for (int x = 1; i + x * 2 < s.size(); x++)
  {
   string tr = s.substr(i, x);
   reverse(tr.begin(), tr.end());
   if (tr != s.substr(s.size() - x, x))
    continue;
   for (int j = i + x; j < s.size(); j++)
    for (int d = 1; j + d + x <= s.size(); d += 2)
     if (BestLen < 2 * x + d && IsPal(s.substr(j, d)))
     {
      BestLen = 2 * x + d;
      res.clear();
      res.push_back(make_pair(i + 1, x));
      res.push_back(make_pair(j + 1, BestLen - 2 * x));
      res.push_back(make_pair(s.size() - x + 1, x));
     }
  }
 }
 return res;
}

string RandS()
{
 string res;
 int n = rand() % 100 + 1;
 for (int i = 0; i < (int)(10); i++)
  res += (char) ('a' + rand() % 2);
 return res;
}


void Check(string s, vec v)
{
 if (v.size() == 1)
  ASS(v[0].second & 1);
 else
 {
  ASS(v.size() == 3);
  ASS(v[1].second & 1);
 }
 for (int i = 0; i < (int)(v.size() - 1); i++)
  ASS(v[i].first + v[i].second <= v[i + 1].first);

 string pal;

 for (int i = 0; i < (int)(v.size()); i++)
  pal += s.substr(v[i].first - 1, v[i].second);

 ASS(IsPal(pal));

}

int main()
{
# 358 "data/708.cpp"
 scanf("%s", s);
 string str(s);
 vec v = Solve(str);
 printf("%d\n", v.size());
 for (int i = 0; i < (int)(v.size()); i++)
  printf("%d %d\n", v[i].first, v[i].second);
 return 0;
}
