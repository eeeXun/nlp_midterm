}
}
# 6 "data/768.cpp" 2


# 7 "data/768.cpp"
using namespace std;

const int MAXN = 1010101;

int l, p[MAXN], ks[MAXN], kt[MAXN], fr[MAXN], e[MAXN], ans, le[MAXN], mid;
clock_t last, now;
double tim;
char s[MAXN], t[MAXN];

void init()
{
 scanf("%s", s + 1);
 s[0] = '$';
 l = strlen(s);
}

void Manacher()
{
 int edge = 0, mid = 0;
 for(int i = 1; i < l; i ++)
 {
  if(edge > i)
   p[i] = min(p[2 * mid - i], edge - i + 1);
  else
   p[i] = 1;
  for(int j = i + p[i]; j < l; j ++)
   if(s[j] == s[i * 2 - j])
    p[i] ++;
   else
    break;
  if(p[i] + i - 1 > edge)
  {
   edge = p[i] + i - 1;
   mid = i;
  }
 }
}

void ExKmp()
{
 last = clock();
 for(int i = l - 1; i >= 1; i --)
  t[i] = s[l - i];
 int z = 0;
 for(int i = 2; i < l; i ++)
 {
  int lth, over;
  if(kt[z] + z <= i)
   lth = 0;
  else
   lth = min(kt[z] + z - i, kt[i - z + 1]);
  for(int j = i + lth; j < l; j ++)
  {
   if(t[j] != t[j - i + 1])
   {
    over = j - 1;
    break;
   }
   if(j == l - 1)
    over = j;
  }
  kt[i] = over - i + 1;
  if(over > kt[z] + z - 1)
   z = i;
 }
 now = clock();
 tim = now - last;

 last = clock();
 z = 0;
 for(int i = 1; i < l; i ++)
 {
  int lth, over;
  if(ks[z] + z <= i)
   lth = 0;
  else
   lth = min(ks[z] + z - i, kt[i - z + 1]);
  for(int j = i + lth; j < l; j ++)
  {
   if(s[j] != t[j - i + 1])
   {
    over = j - 1;
    break;
   }
   if(j == l - 1)
    over = j;
  }
  ks[i] = over - i + 1;
  if(over > ks[z] + z - 1)
   z = i;
 }
 now = clock();
 tim = now - last;

}

void process()
{
 last = clock();
 Manacher();
 now = clock();
 tim = now - last;

 last = clock();
 ExKmp();
 now = clock();
 tim = now - last;

 last = clock();
 memset(e, 63, sizeof(e));
 for(int i = l - 1; i >= 1; i --)
  if(ks[i])
   e[ks[i] + i - 1] = i;
 for(int i = l - 1; i >= 1; i --)
  e[i] = min(e[i], e[i + 1]);
 for(int i = 1; i < l; i ++)
 {
  fr[i] = fr[i - 1];
  le[i] = le[i - 1];
  if(e[i] <= MAXN && i - e[i] + 1 > fr[i])
  {
   fr[i] = i - e[i] + 1;
   le[i] = e[i];
  }
 }
 for(int i = 1; i < l; i ++)
 {

  int lth = fr[i - p[i]] * 2 + p[i] * 2 - 1;
  if(fr[i - p[i]] >= l - i - p[i])
   lth = (l - i) * 2 - 1;
  if(lth > ans)
  {
   ans = lth;
   mid = i;
  }
 }
 if(fr[mid - p[mid]] >= l - mid - p[mid] && le[mid - p[mid]] + fr[mid - p[mid]] == mid - p[mid] + 1)
  printf("1\n%d %d\n", 2 * mid - l + 1, (l - mid) * 2 - 1);
 else
 {
  int t = min(fr[mid - p[mid]], l - mid - p[mid]);
  if(!t)
   printf("1\n%d %d\n", mid - p[mid] + 1, p[mid] * 2 - 1);
  else
   printf("3\n%d %d\n%d %d\n%d %d\n", le[mid - p[mid]], t, mid - p[mid] + 1, p[mid] * 2 - 1, l - t, t);
 }
 last = clock();
 now = clock();
 tim = now - last;

}

int main()
{
 last = clock();
 init();
 now = clock();
 tim = now - last;

 process();
 return 0;
}
