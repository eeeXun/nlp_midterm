
   if (!__testin)
     this->setg(__endg, __endg, __endg);
 }
    }

  template <class _CharT, class _Traits, class _Alloc>
    void
    basic_stringbuf<_CharT, _Traits, _Alloc>::
    _M_pbump(char_type* __pbeg, char_type* __pend, off_type __off)
    {
      this->setp(__pbeg, __pend);
      while (__off > __gnu_cxx::__numeric_traits<int>::__max)
 {
   this->pbump(__gnu_cxx::__numeric_traits<int>::__max);
   __off -= __gnu_cxx::__numeric_traits<int>::__max;
 }
      this->pbump(__off);
    }




  extern template class basic_stringbuf<char>;
  extern template class basic_istringstream<char>;
  extern template class basic_ostringstream<char>;
  extern template class basic_stringstream<char>;


  extern template class basic_stringbuf<wchar_t>;
  extern template class basic_istringstream<wchar_t>;
  extern template class basic_ostringstream<wchar_t>;
  extern template class basic_stringstream<wchar_t>;




}
# 1218 "/usr/include/c++/11.2.0/sstream" 2 3
# 11 "data/36.cpp" 2

# 11 "data/36.cpp"
using namespace std;


const long long N = 1e6 + 10;

char c[N];
char s[N];
char t[N];
long long net[N] , suf[N] , sux[N] , sua[N];
long long p[N];

signed main()
{
 ios::sync_with_stdio(false);
 cin >> (c + 1);
 long long n = strlen(c + 1);







 for (long long i = 1; i <= n; ++i) {
  s[i * 2 - 1] = c[i];
  s[i * 2] = '#';
 }
# 72 "data/36.cpp"
 p[1] = 1; long long mid = 1, Maxr(1);
 for (long long i = 2, N = n << 1; i <= N; ++i) {
  if (i < Maxr) p[i] = std::min(p[(mid << 1) - i], p[mid] - (i - mid));
  else p[i] = 1;
  while (s[i - p[i]] == s[i + p[i]]) ++p[i];
  if (i + p[i] > Maxr) {
   Maxr = i + p[i]; mid = i;
  }

 }
 for (long long i = 3; i <= (n << 1); i += 2) {
  if (s[i + p[i]] == '#') p[i]--;
  else p[i] -= 2;
  p[(i >> 1) + 1] = p[i] + 1;
 }
 for (register long long i = 1; i <= (n >> 1); i++)
 {
  t[i] = c[n + 1 - i];
  t[n + 1 - i] = c[i];
 }
 for (register long long i = 2, j = 0; i <= n; i++)
 {
  while (t[j + 1] != t[i] && j != 0)
  {
   j = net[j];
  }
  if (t[j + 1] == t[i])
  {
   j++;
   net[i] = j;
  }
  else
  {
   net[i] = 0;
  }
 }
 for (register long long i = 1, j = 0; i <= n; i++)
 {
  while (t[j + 1] != c[i] && j != 0)
  {
   j = net[j];
  }
  if (t[j + 1] == c[i])
  {
   j++;
   suf[i] = j;
  }
  else
  {
   suf[i] = 0;
  }
 }
 for (register long long i = 1; i <= n; i++)
 {
  if (suf[i] >= sux[i - 1])
  {
   sux[i] = suf[i];
   sua[i] = i;
  }
  else
  {
   sux[i] = sux[i - 1];
   sua[i] = sua[i - 1];
  }
 }
 long long ans = 0;
 long long az = 0, al = 0;
 for (register long long i = 1; i <= n; i++)
 {

  if (ans < p[i] + (min((sux[i - (p[i] >> 1) - 1]), n - (i + (p[i] >> 1))) << 1))
  {
   ans = p[i] + (min((sux[i - (p[i] >> 1) - 1]), n - (i + (p[i] >> 1))) << 1);
   az = i;
   al = sua[i - (p[i] >> 1) - 1];
  }
 }
 if ((n - (az + (p[az] >> 1))) && al && suf[al])
 {
  cout << 3 << endl;
  long long len = min(suf[al], n - (az + (p[az] >> 1)));
  cout << al - len + 1 << " " << len << endl;
  cout << az - (p[az] >> 1) << " " << p[az] << endl;
  cout << n - len + 1 << " " << len;
 }
 else
 {
  cout << 1 << endl;
  cout << az - (p[az] >> 1) << " " << p[az];
 }
 return 0;
}
