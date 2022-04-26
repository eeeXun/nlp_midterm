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
# 3 "data/870.cpp" 2







# 9 "data/870.cpp"
using namespace std;

pair<int, int> eea(int a, int b) {
 if(b == 0)
  return make_pair(1, 0);
 auto ret = eea(b, a%b);
 return make_pair(ret.second, ret.first - a/b*ret.second);
}

struct Modint {
 int val;

 Modint(int nval = 0) {
  val = nval;
 }

 Modint& operator+=(Modint r) {
  val = (val + r.val) % 1000000007;
  return *this;
 }
 Modint& operator-=(Modint r) {
  val = (val + 1000000007 - r.val) % 1000000007;
  return *this;
 }
 Modint& operator*=(Modint r) {
  val = 1LL * val * r.val % 1000000007;
  return *this;
 }
 Modint& operator/=(Modint r) {
  int ret = (eea(r.val, 1000000007).first + 1000000007) % 1000000007;
  return operator*=(ret);
 }

 Modint operator+(Modint r) {return Modint(*this)+=r;}
 Modint operator-(Modint r) {return Modint(*this)-=r;}
 Modint operator*(Modint r) {return Modint(*this)*=r;}
 Modint operator/(Modint r) {return Modint(*this)/=r;}
};

Modint hpow[100001], hpowrev[100001];

struct Hashstring {
 vector<Modint> hash;

 void construct(string base, int offset) {
  hash.resize(base.size() + 1, 0);
  for(int i=0;i<(int)base.size();i++)
   hash[i+1] = hash[i] + hpow[i] * ( (base[i]-'a' + offset) % 30);
 }

 Modint segment(int l, int r) {
  return (hash[r] - hash[l]) * hpowrev[l];
 }
};


pair<int, int> inReverse(pair<int, int> val, int n) {
 return make_pair(n - val.second, n - val.first);
}


Hashstring forwhash[4], revhash[4];

bool valid(pair<int, int> span, pair<int, int> revspan) {
 for(int i=0;i<4;i++)
  if(forwhash[i].segment(span.first, span.second).val != revhash[i].segment(revspan.first, revspan.second).val)
   return false;
 return true;
}

bool isPalindrome(pair<int, int> span, int n) {
 pair<int, int> revspan = make_pair(0, span.first+1);
 revspan.first = revspan.second - (span.second - span.first);

 if(span.second > n || revspan.first < 0)
  return false;
 return valid(span, inReverse(revspan, n) );
}





int main() {
 ios_base::sync_with_stdio(false);
 cin.tie(0);

 hpow[0] = 1;
 hpowrev[0] = 1;
 hpow[1] = 30;
 hpowrev[1] = Modint(1) / hpow[1];

 for(int i=2;i<=100000;i++) {
  hpow[i] = hpow[i-1] * hpow[1];
  hpowrev[i] = hpowrev[i-1] * hpowrev[1];
 }


 string second;
 cin >> second;
 int n = second.size();

 for(int i=0;i<4;i++)
  forwhash[i].construct(second, i);
 reverse(second.begin(), second.end() );
 for(int i=0;i<4;i++)
  revhash[i].construct(second, i);


 vector<int> edgelen(n+1, 0), edgelast(n+1, 0);

 {
  for(int i=0;i<n;i++) {
   int len = 0;

   for(int tpow = (1<<19); tpow >0; tpow /= 2)
    if(i+len+tpow <= n && valid(make_pair(i, i+len+tpow), make_pair(0, len+tpow) ) )
     len += tpow;
   edgelen[i+len] = max(edgelen[i+len], len);
  }

  edgelast[n] = n;
  for(int i=n-1;i>=0;i--) {
   edgelast[i] = i;
   edgelen[i] = max(edgelen[i], edgelen[i+1] - 1);
  }

  for(int i=1;i<=n;i++)
   if(edgelen[i-1] > edgelen[i]) {
    edgelen[i] = edgelen[i-1];
    edgelast[i] = edgelast[i-1];
   }

 }



 pair<int, vector<pair<int, int> > > result;
 for(int i=0;i<n;i++) {

  int len = 0;
  for(int tpow = 1<<19; tpow > 0; tpow /= 2)
   if(isPalindrome(make_pair(i, i+len+tpow), n) )
    len += tpow;

  int elen = min(edgelen[i-len+1], n - len - i);
  int csz = elen * 2 + len*2-1;
  vector<pair<int, int> > spans;

  if(elen > 0)
   spans.push_back(make_pair(edgelast[i-len+1] - edgelen[i-len+1], elen) );

  spans.push_back(make_pair(i-len+1, 2*len-1));

  if(elen > 0)
   spans.push_back(make_pair(n-elen, elen) );

  result = max(result, make_pair(csz, spans) );
 }

 cout << result.second.size() << '\n';
 for(auto c : result.second)
  cout << c.first+1 << ' ' << c.second << '\n';
 return 0;
}
