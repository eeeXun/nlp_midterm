# 129 "/usr/lib/gcc/x86_64-pc-linux-gnu/11.2.0/include/wmmintrin.h" 3 4
#pragma GCC pop_options
# 5 "data/386.cpp" 2

# 5 "data/386.cpp"
using ul = std::uint32_t;
using ull = std::uint64_t;
using li = std::int32_t;
using ll = std::int64_t;
using llf = long double;
using uss = std::uint8_t;

const ul maxlen = 1e5;

char s[maxlen + 1 + maxlen + 1];

ul len;

ul kmp[maxlen + 1 + maxlen + 1];

ul v[maxlen + 1];

ul mxvid[maxlen + 1];

ul plen[maxlen + 1];

int main()
{
 std::scanf("%s", s + 1);
 len = std::strlen(s + 1);
 std::memcpy(s + len + 2, s + 1, len);
 std::reverse(s + 1, s + len + 1);
 kmp[1] = 0;
 for (ul i = 2, j; i <= len + 1 + len; ++i) {
  for (j = kmp[i - 1]; j && s[j + 1] != s[i]; j = kmp[j]);
  if (s[j + 1] == s[i]) {
   kmp[i] = j + 1;
  } else {
   kmp[i] = 0;
  }
 }
 std::memcpy(s + 1, s + len + 2, len);
 std::memcpy(v + 1, kmp + len + 2, sizeof(ul) * len);
 for (ul i = 1; i <= len; ++i) {
  mxvid[i] = v[i] > v[mxvid[i - 1]] ? i : mxvid[i - 1];
 }
 for (ul i = 1, mxid = 0; i <= len; ++i) {
  if (mxid + plen[mxid] < i) {
   plen[i] = 0;
  } else {
   plen[i] = std::min(plen[mxid + mxid - i], plen[mxid] + mxid - i);
  }
  while (i + plen[i] != len && i - plen[i] != 1 && s[i + plen[i] + 1] == s[i - plen[i] - 1]) {
   ++plen[i];
  }
  if (mxid + plen[mxid] < i + plen[i]) {
   mxid = i;
  }
 }
 ul ans = 0;
 ul x1, l1, x2, l2, x3, l3;
 for (ul i = 1; i <= len; ++i) {
  ul tx2 = i - plen[i];
  ul tl2 = plen[i] + plen[i] + 1;
  ul tl1 = v[mxvid[tx2 - 1]];
  ul tx1 = mxvid[tx2 - 1] - tl1 + 1;
  if (tl1 > len - (tx2 + tl2 - 1)) {
   tl1 = len - (tx2 + tl2 - 1);
  }
  ul tl3 = tl1;
  ul tx3 = len - tl3 + 1;
  if (tl1 + tl2 + tl3 > ans) {
   ans = tl1 + tl2 + tl3;
   x1 = tx1;
   x2 = tx2;
   x3 = tx3;
   l1 = tl1;
   l2 = tl2;
   l3 = tl3;
  }
 }
 if (!l1) {
  std::printf("1\n%u %u\n", x2, l2);
 } else {
  std::printf("3\n%u %u\n%u %u\n%u %u\n", x1, l1, x2, l2, x3, l3);
 }
 return 0;
}
