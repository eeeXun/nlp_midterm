# 5 "data/288.cpp" 2

# 5 "data/288.cpp"
using namespace std;

int first[100001];
int rev[100001];
int d[100001];

vector<int> prefix(string S, string T)
{
 string str = T + "#" + S;
 int N = str.length();
 vector<int> pr(N);
 for (int i = 1; i < N; i++)
 {
  int j = pr[i - 1];
  while (j > 0 && str[i] != str[j])
   j = pr[j - 1];
  if (str[i] == str[j])
   j++;
  pr[i] = j;
 }
 pr.erase(pr.begin(), pr.begin() + T.length() + 1);
 return pr;
}

int main()
{
 string S;
 cin >> S;
 string T = S;
 reverse(T.begin(), T.end());
 vector<int> pr = prefix(S, T);

 int N = S.length();

 int l = 0, r = -1;
 for (int i = 0; i < N; i++)
 {
  int k = i > r ? 0 : min(r - i, d[l + r - i]);
  while (i + k < N && i - k >= 0 && S[i + k] == S[i - k])
   ++k;
  d[i] = k--;
  if (i + k > r)
  {
   l = i - k;
   r = i + k;
  }
 }

 for (int i = 0; i < N+1; i++)
  first[i] = -1;

 for (int i = 0; i < N; i++)
 {
  if (i > 0)
   rev[i] = rev[i - 1];
  else
   rev[i] = 0;

  if (pr[i] > rev[i])
  {
   rev[i] = pr[i];
   first[pr[i]] = i;
  }
 }

 int side = 0;
 int mid = 1;
 int pal = 0;

 for (int i = 1; i < N; i++)
 {
  int md = min(min(d[i], i+1), N-i);
  int sd = min(rev[i - md], N - i - md);
  if (mid + side < md + sd)
  {
   mid = md;
   side = sd;
   pal = i;
  }
 }

 if (side > 0)
 {
  cout << 3 << endl;
  cout << first[side] - side + 2 <<' ' << side <<endl;
  cout << pal - mid + 2 << ' ' << mid * 2 - 1 <<endl;
  cout << N - side + 1 << ' ' << side;
 }
 else
 {
  cout << 1 << endl;
  cout << pal - mid + 2 << ' ' << mid * 2 - 1;
 }
}
