
template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
includes(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2,
         _ForwardIterator2 __last2);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator,
          class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_union(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2,
          _ForwardIterator2 __last2, _ForwardIterator __result, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_union(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2,
          _ForwardIterator2 __last2, _ForwardIterator __result);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator,
          class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_intersection(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                 _ForwardIterator2 __first2, _ForwardIterator2 __last2, _ForwardIterator __result, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_intersection(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                 _ForwardIterator2 __first2, _ForwardIterator2 __last2, _ForwardIterator __result);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator,
          class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_difference(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
               _ForwardIterator2 __first2, _ForwardIterator2 __last2, _ForwardIterator __result, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_difference(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
               _ForwardIterator2 __first2, _ForwardIterator2 __last2, _ForwardIterator __result);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator,
          class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_symmetric_difference(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                         _ForwardIterator2 __first2, _ForwardIterator2 __last2, _ForwardIterator result,
                         _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
set_symmetric_difference(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                         _ForwardIterator2 __first2, _ForwardIterator2 __last2, _ForwardIterator __result);


template <class _ExecutionPolicy, class _RandomAccessIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _RandomAccessIterator>
is_heap_until(_ExecutionPolicy&& __exec, _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _RandomAccessIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _RandomAccessIterator>
is_heap_until(_ExecutionPolicy&& __exec, _RandomAccessIterator __first, _RandomAccessIterator __last);

template <class _ExecutionPolicy, class _RandomAccessIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
is_heap(_ExecutionPolicy&& __exec, _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _RandomAccessIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
is_heap(_ExecutionPolicy&& __exec, _RandomAccessIterator __first, _RandomAccessIterator __last);



template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
min_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
min_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);

template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
max_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, _ForwardIterator>
max_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);

template <class _ExecutionPolicy, class _ForwardIterator, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, std::pair<_ForwardIterator, _ForwardIterator>>
minmax_element(_ExecutionPolicy&& __exec, _ForwardIterator __first, _ForwardIterator __last);



template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2, class _Compare>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2, _Compare __comp);

template <class _ExecutionPolicy, class _ForwardIterator1, class _ForwardIterator2>
__pstl::__internal::__enable_if_execution_policy<_ExecutionPolicy, bool>
lexicographical_compare(_ExecutionPolicy&& __exec, _ForwardIterator1 __first1, _ForwardIterator1 __last1,
                        _ForwardIterator2 __first2, _ForwardIterator2 __last2);

}
# 75 "/usr/include/c++/11.2.0/algorithm" 2 3
# 120 "data/618.cpp" 2



# 122 "data/618.cpp"
using namespace std;

const int MAXN = 200020 + 1;
const int MAXM = 22 + 1;

int n, T[MAXN], SA[MAXN], RANK[MAXN], H[MAXN], RMQ[MAXM][MAXN], LOG2[MAXN];
char str[MAXN], revstr[MAXN];

inline void calcRMQ(int n, int * H) {
 for (int i = 0; i < n; i++) RMQ[0][i] = H[i];
 for (int len = 1; 1 << len <= n; len++) {
  for (int i = n - (1 << len); i >= 0; i--) RMQ[len][i] = min(RMQ[len - 1][i], RMQ[len - 1][i + (1 << (len - 1))]);
 }
}

inline void initLOG2(int n) {
 for (int i = 0; 1 << i <= n; i++) LOG2[1 << i] = i;
 for (int mask = 2; mask <= n; mask++) {
  if (!LOG2[mask]) LOG2[mask] = LOG2[mask - 1];
 }
}

inline int queryRMQ(int x, int y) {
 int len = LOG2[y - x + 1];
 return min(RMQ[len][x], RMQ[len][y - (1 << len) + 1]);
}

int fail[MAXN], fit[MAXN], maxlen[MAXN], mmax[MAXN], prev[MAXN];

inline void KMP(int lenstr, const char * str, int lenpat, const char * pat) {
 int i, j;
 memset(fail, 0xFF, sizeof(int) * (lenpat + 1));
 for (j = 1; j < lenpat; j++) {
  for (i = fail[j - 1]; i >= 0 && pat[i + 1] != pat[j]; i = fail[i]);
  if (pat[i + 1] == pat[j]) fail[j] = i + 1;
  else fail[j] = -1;
 }
 for (i = j = 0; i < lenstr; i++) {
  if (str[i] == pat[j]) {
   fit[i] = ++j;
   if (j == lenpat) j = fail[j - 1] + 1;
  } else if (j) {
   j = fail[j - 1] + 1;
   i--;
  }
 }
}

vector < pair <int, int> > ans;

int main() {
 scanf("%s", str);
 n = (int)strlen(str);
 for (int i = 0, j = (n << 1) - 1; i < n; i++, j--) T[i] = T[j] = str[i] - 'a' + 1;
 suffixArray(T, SA, n << 1, 26);
 for (int i = 0; i < n << 1; i++) RANK[SA[i]] = i;
 calcHeight(T, SA, H, n << 1);
 calcRMQ(n << 1, H);
 initLOG2(n << 1);
 for (int i = 0; i < n; i++) {
  int x = min(RANK[i], RANK[(n << 1) - 1 - i]) + 1, y = max(RANK[i], RANK[(n << 1) - 1 - i]);
  maxlen[i] = min(queryRMQ(x, y), n - i);
 }
 strcpy(revstr, str);
 reverse(revstr, revstr + n);
 KMP(n, str, n, revstr);

 mmax[0] = fit[0];
 prev[0] = 0;
 for (int i = 1; i < n; i++) {
  if (fit[i] > mmax[i - 1]) {
   mmax[i] = fit[i];
   prev[i] = i;
  } else {
   mmax[i] = mmax[i - 1];
   prev[i] = prev[i - 1];
  }
 }

 int res = 0;
 for (int i = 0; i < n; i++) {
  int x = i - maxlen[i] + 1, y = i + maxlen[i] - 1, tmplen;
  vector < pair <int, int> > tmpans;
  if (!x || y == n - 1) {
   tmplen = y - x + 1;
   tmpans.push_back(make_pair(x, y));
  } else {
   int idx = lower_bound(mmax, mmax + x, n - y) - mmax - 1;
   if (idx < 0 || !mmax[idx]) {
    tmplen = y - x + 1;
    tmpans.push_back(make_pair(x, y));
   } else {
    tmplen = (mmax[idx] << 1) + (y - x + 1);
    tmpans.push_back(make_pair(prev[idx] - mmax[idx] + 1, prev[idx]));
    tmpans.push_back(make_pair(x, y));
    tmpans.push_back(make_pair(n - mmax[idx], n - 1));
   }
  }
  if (res < tmplen) {
   res = tmplen;
   ans = tmpans;
  }
 }
 printf("%d\n", (int)ans.size());
 for (int i = 0; i < (int)ans.size(); i++) printf("%d %d\n", ans[i].first + 1, ans[i].second - ans[i].first + 1);
 return 0;
}
