



extern int strverscmp (const char *__s1, const char *__s2)
     noexcept (true) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strfry (char *__string) noexcept (true) __attribute__ ((__nonnull__ (1)));


extern void *memfrob (void *__s, size_t __n) noexcept (true) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__read_write__, 1, 2)));







extern "C++" char *basename (char *__filename)
     noexcept (true) __asm ("basename") __attribute__ ((__nonnull__ (1)));
extern "C++" const char *basename (const char *__filename)
     noexcept (true) __asm ("basename") __attribute__ ((__nonnull__ (1)));
# 539 "/usr/include/string.h" 3 4
}
# 30 "/usr/include/memory.h" 2 3 4
# 24 "data/469.cpp" 2


# 25 "data/469.cpp"
using namespace std;
# 42 "data/469.cpp"
const int INF = 1000 * 1000 * 1000;
const long long INF64 = 1000LL * 1000LL * 1000LL * 1000LL * 1000LL * 1000LL;

char s[100500];

string x;
int z[2 * 100500];
pair <int, int> ref[100500];
int pal[100500];
int n;

inline void z_func()
{
 int l, r, q;
 z[0] = l = r = 0;
 for (int k = 1; k < (int)x.size(); k++)
 {
  if (k > r)
  {
   q = k;
   while (q < (int)x.size() && x[q] == x[q - k])
    q++;
   z[k] = q - k;
   l = k;
   r = q - 1;
  }
  else
  {
   if (z[k - l] < r - k + 1)
    z[k] = z[k - l];
   else
   {
    q = r + 1;
    while (q < (int)x.size() && x[q] == x[q - k])
     q++;
    z[k] = q - k;
    l = k;
    r = q - 1;
   }
  }
 }
}


void Load()
{
 gets (s);
 n = strlen(s);
 x = (string)s;
 reverse (x.begin(), x.end());
 x = x + "#" + (string)s;
}

void Solve()
{
 for (int i = 0; i < n; i++)
  ref[i].first = ref[i].second = -1;

 z_func();
 int last = 0;

 for (int i = n + 1; i < (int)x.size(); i++)
  if (z[i] > last)
  {
   if (i + (z[i] << 1) + 1 < (int)x.size())
   {
    ref[i - n - 1].first = z[i];
    ref[i - n - 1].second = i - n - 1;
   }
   last = z[i];
  }
 for (int i = 1; i < n; i++)
  ref[i] = max (ref[i], ref[i - 1]);

 int l, r, k, mx;
 mx = 0;
 l = 0, r = -1;
 for (int i = 0; i < n; i++)
 {
  k = (r < i ? 0 : min (pal[l + r - i], r - i)) + 1;
  while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
   k++;
  pal[i] = --k;
  if (i + k > r)
  {
   l = i - k;
   r = i + k;
  }

  int pre_len = 0;
  int pos = i - pal[i] - 1;
  if (pos < 0)
   mx = max (mx, (pal[i] << 1) + 1);
  else
  {
   pre_len = ref[pos].first;
   if (pre_len == -1)
    mx = max (mx, (pal[i] << 1) + 1);
   else
   {
    pre_len = min (pre_len, pos - ref[pos].second + 1);
    pre_len = min (pre_len, n - i - pal[i] - 1);
    mx = max (mx, (pal[i] << 1) + 1 + (pre_len << 1) + 1);
   }

  }
 }

 for (int i = 0; i < n; i++)
 {
  int pre_len = 0;
  int pos = i - pal[i] - 1;
  if (pos < 0)
   k = (pal[i] << 1) + 1;
  else
  {
   pre_len = ref[pos].first;
   if (pre_len == -1)
    k = (pal[i] << 1) + 1;
   else
   {
    pre_len = min (pre_len, pos - ref[pos].second + 1);
    pre_len = min (pre_len, n - i - pal[i] - 1);
    k = (pal[i] << 1) + 1 + (pre_len << 1) + 1;
   }

  }
  if (k == mx)
  {
   if ((pal[i] << 1) + 1 == k)
    printf ("1\n%d %d", pos + 2, (pal[i] << 1) + 1);
   else
   {
    printf ("3\n");
    printf ("%d %d\n", ref[pos].second + 1, pre_len);
    printf ("%d %d\n", pos + 2, (pal[i] << 1) + 1);
    printf ("%d %d\n", n - pre_len + 1, pre_len);
   }

   return;
  }
 }
}

int main()
{


 freopen("in", "rt", 
# 190 "data/469.cpp" 3 4
                    stdin
# 190 "data/469.cpp"
                         );
 freopen("out", "wt", 
# 191 "data/469.cpp" 3 4
                     stdout
# 191 "data/469.cpp"
                           );

 Load();
 Solve();
 return 0;
}
