# 40 "/usr/include/c++/11.2.0/cctype" 3
# 6 "data/793.cpp" 2

# 6 "data/793.cpp"
using namespace std;

int p[220010];
int res[100005];
int _next[220010];
int f[100005];
char s[220010], t[100005];

int manacher(char *s, int &pos)
{
 int r = 0;
 int c = 0;
 int len = strlen(s)-1, ans = 0;
 for(int i = 1; i <= len; i++)
 {
  if(i < r)
   p[i] = min(r-i, p[2*c-i]);
  else
   p[i] = 1;
  while(s[i+p[i]] == s[i-p[i]])
   p[i]++;
  if(i+p[i] > r)
  {
   r = i+p[i];
   c = i;
  }
  if(i%2 == 0)
  {
   res[i/2] = p[i]-1;
   if(ans < p[i])
   {
    ans = p[i];
    pos = i/2;
   }
  }
 }
 return ans-1;
}

signed main()
{

 char ch;
 int cnt = 0;
 scanf("%s", t+1);
 int len = strlen(t+1);

 for(int i = 1; i <= len; i++)
 {
  s[++cnt] = '#';
  s[++cnt] = t[i];
 }
 s[0] = '%';
 s[++cnt] = '#';
 s[++cnt] = '\0';
 int pos;
 int ans = manacher(s, pos);


 cnt = 0;
 for(int i = len; i >= 1; i--)
  s[++cnt] = t[i];
 s[++cnt] = '#';
 s[++cnt] = 0;
 strcat(s+1, t+1);
 _next[1] = 0;
 for(int i = 2, j = 0; i <= 2*len+1; i++)
 {
  while(j && s[j+1] != s[i])
   j = _next[j];
  if(s[j+1] == s[i])
   j++;
  _next[i] = j;
 }
 for(int i = 1; i <= len; i++)
  f[i] = max(f[i-1], _next[len+1+i]);
 int _max = 0, mid;
 for(int i = 1; i <= len; i++)
 {

  if(res[i]+2*min(f[i-res[i]/2-1], len-i-res[i]/2) > _max)
  {
   _max = res[i]+2*min(f[i-res[i]/2-1], len-i-res[i]/2);
   mid = i;
  }
 }
 if(ans >= _max)
  printf("1\n%d %d", pos-ans/2, ans);
 else
 {

  int prer, prel, prelen;
  for(int i = 1; i <= len; i++)
   if(_next[len+1+i] == f[mid-res[mid]/2-1])
   {
    prer = i;
    break;
   }
  prel = prer-_next[len+1+prer]+1;
  prelen = min(_next[len+1+prer], len-mid-res[mid]/2);
  printf("3\n%d %d\n%d %d\n%d %d", prel, prelen, mid-res[mid]/2, res[mid], len-prelen+1, prelen);
 }
    return 0;
}
