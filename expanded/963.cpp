
}
# 45 "/usr/include/c++/11.2.0/cassert" 2 3
# 10 "data/963.cpp" 2

# 10 "data/963.cpp"
using namespace std;






class RMQ_ST
{
  private:
    const static int RMQ_LOGMAX = 20;
    const static int RMQ_MAXN = 201000;


    vector<int> intLen;


    int M[RMQ_MAXN][RMQ_LOGMAX];

  public:

    vector<int> value;

  private:
    int N;


    inline int getIntLen(int key)
    {
      int len = 0;
      while (key>0)
      {
        len++;
        key >>= 1;
      }
      return len;
    }

  public:
    RMQ_ST(int n)
    {
      N = n;
      
# 52 "data/963.cpp" 3 4
     (static_cast <bool> (
# 52 "data/963.cpp"
     N <= RMQ_MAXN
# 52 "data/963.cpp" 3 4
     ) ? void (0) : __assert_fail (
# 52 "data/963.cpp"
     "N <= RMQ_MAXN"
# 52 "data/963.cpp" 3 4
     , "data/963.cpp", 52, __extension__ __PRETTY_FUNCTION__))
# 52 "data/963.cpp"
                          ;
      intLen = vector<int>(N);
      value = vector<int>(N);

      for (int i = 0; i < N; ++i)
        intLen[i] = getIntLen(i);
    }

    inline void setValue(int posi , int value)
    { this->value[posi] = value; }


    void initRMQ()
    {
      for (int i = 0; i < N; ++i)
        M[i][0] = i;
      for (int j = 1; (1 << j) <= N; ++j)
      {
        int upper = N + 1 - (1 << j);
        int step = 1 << (j - 1);
        for (int i = 0; i < upper; ++i)
        {
          if (value[M[i][j-1]] < value[M[i+step][j-1]])
            M[i][j] = M[i][j-1];
          else
            M[i][j] = M[i+step][j-1];
        }
      }
    }


    int RMQ_value(int start,int stop)
    {
      int k = (stop - start +1);
      k = intLen[k] - 1;
      return min(value[M[start][k]] , value[M[stop-(1<<k)+1][k]]);
    }


    int RMQ_posi(int start,int stop)
    {
      int k = (stop - start + 1);
      k = intLen[k] - 1;
      if (value[M[start][k]] <= value[M[stop-(1<<k)+1][k]])
        return M[start][k];
      else
        return M[stop-(1<<k)+1][k];
    }
};

class BucketSort
{
  public:
# 114 "data/963.cpp"
    static void sort(vector<pair<int, int> > & data, vector<int> & ret, vector<int> & _count, vector<int> & _sum)
    {
      int N = data.size();
      int M = _count.size();
      for (int i = 0; i < M; ++i) _count[i] = 0;
      for (int i = 0; i < N; ++i) _count[data[i].first]++;
      _sum[0] = _count[0];
      for (int i = 1; i < M; ++i) _sum[i] = _sum[i - 1] + _count[i];


      for (int i = 0; i < N; ++i)
      {
        int key = data[i].first;
        int ID = data[i].second;
        int offset = _sum[key] - _count[key];
        ret[offset] = ID;
        _count[key]--;
      }
    }
};

class SuffixArray
{
  public:
    vector<int> rankToID;
    vector<int> IDtoRank;
    vector<int> IDtoRank2;
    vector<int> _count;
    vector<int> _sum;
    vector<int> ret;
    vector<pair<int, int> > data;
    vector<int> height;

    RMQ_ST * rmq;

    int L;
    string str;






    SuffixArray(const string & _str)
    {
      L = _str.length();
      str = _str;
      rankToID = vector<int>(L);
      IDtoRank = vector<int>(L);
      IDtoRank2 = vector<int>(L);
      _count = vector<int>(L);
      _sum = vector<int>(L);
      ret = vector<int>(L);
      data = vector<pair<int, int> >(L);
      height = vector<int>(L);

      sortSuffix();
      calHeight();

      rmq = new RMQ_ST(L);
      for (int i = 0; i < L; ++i)
        rmq->setValue(i, height[i]);
      rmq->initRMQ();
    }

    int getLCS(int l, int r)
    {
      if (l == r) return L - l;
      int rank1 = IDtoRank[l];
      int rank2 = IDtoRank[r];
      if (rank1 > rank2) swap(rank1, rank2);
      return rmq->RMQ_value(rank1 + 1, rank2);
    }

    int getC;

    inline int getNowRank(int id)
    { return id >= L ? 0 : IDtoRank[id]; }

    void calHeight()
    {
      int j = 0;
      height[0] = 0;
      for (int i = 0; i < L; ++i)
      {
        int nowID = i;
        int nowRank = IDtoRank[i];
        int lastRank = nowRank - 1;
        int lastID = rankToID[lastRank];
        if (nowRank == 0) continue;
        while (true)
          if (str[nowID + j] == str[lastID + j]) j++;
          else break;
        height[nowRank] = j;
        if (j > 0) j--;
      }
    }

    void sortSuffix()
    {

      vector<vector<int> > initBucket(256);
      for (int i = 0; i < L; ++i)
        initBucket[str[i] + 128].push_back(i);

      int nowR = 0;
      for (int i = 0; i < initBucket.size(); ++i)
      {
        for (int j = 0; j < initBucket[i].size(); ++j)
          IDtoRank[initBucket[i][j]] = nowR;
        if (initBucket[i].size() > 0) nowR++;
      }

      int k = 1;

      while (true)
      {
        for (int i = 0; i < L; ++i) {
          data[i].first = getNowRank(i + k);
          data[i].second = i;
        }
        BucketSort::sort(data, ret, _count, _sum);

        for (int i = 0; i < L; ++i) {
          int nowID = ret[i];
          data[i].first = getNowRank(nowID);
          data[i].second = nowID;
        }
        BucketSort::sort(data, ret, _count, _sum);

        int nowR = -1;
        for (int i = 0; i < L; ++i) {
          int nowID = ret[i];
          if (i == 0) nowR++;
          else {
            int lastID = ret[i - 1];
            if (getNowRank(nowID) > getNowRank(lastID) || getNowRank(nowID) == getNowRank(lastID) &&
                getNowRank(nowID + k) > getNowRank(lastID + k))
              nowR++;
          }
          IDtoRank2[nowID] = nowR;
        }

        for (int i = 0; i < L; ++i)
          IDtoRank[i] = IDtoRank2[i];

        k = k << 1;
        if (k >= L) break;
      }


      for (int i = 0; i < L; ++i)
        rankToID[IDtoRank[i]] = i;
    }

    bool check()
    {
      for (int i = 0; i < L; ++i)
      {
        int nowID = rankToID[i];
        if (i < L - 1)
        {
          int nextID = rankToID[i + 1];
          string now = str.substr(nowID);
          string next = str.substr(nextID);
          if (now >= next)
            return false;
        }
      }

      for (int i = 1; i < L; ++i)
      {
        int nowID = rankToID[i];
        int lastID = rankToID[i - 1];
        string now = str.substr(nowID);
        string last = str.substr(lastID);

        int same = 0;
        for (int k = 0; k < now.length() && k < last.length(); ++k)
          if (now[k] == last[k])
            same++;
          else
            break;

        if (same != height[i]) return false;
      }
      if (height[0] != 0) return false;
      return true;
    }


    friend ostream & operator << (ostream & out, SuffixArray & array)
    {
      cout << "#####Suffix#####" << endl;
      for (int i = 0; i < array.L; ++i)
        out << array.str.substr(i) << endl;

      cout << "#####Sorted#####" << endl;
      for (int i = 0; i < array.L; ++i)
        out << array.str.substr(array.rankToID[i]) << endl;
      return out;
    }


    void outputNowRank(int k)
    {
      vector<vector<string> > ranks(L);
      for (int i = 0; i < L; ++i) {
        cout << IDtoRank[i] << " " << str.substr(i, k) << " ";
        ranks[IDtoRank[i]].push_back(str.substr(i, k));
      }
      cout << endl;

      for (int i = 0; i < L; ++i) {
        cout << i << " ";
        for (int j = 0; j < ranks[i].size(); ++j)
          cout << ranks[i][j] << " ";
      }
      cout << endl;
    }

};

string getRandomString()
{
  string ret(10, 'a');
  for (int i = 0; i < ret.length(); ++i)
    ret[i] = 'a' + rand() % (2 + rand() % 10);

  return ret + "_";
}

string line;
int N;
SuffixArray * sa;
int firstAppear[500000];

bool isSubStrSame(int l, int ll, int r, int rl)
{
  if (l < 0 || l >= N || l + ll - 1 >= N) return false;
  if (r < 0 || r >= N || r + rl - 1 >= N) return false;
  if (ll != rl) return false;
  int rS = N - 1 - (r + rl - 1) + N + 1;

  int lcs = sa->getLCS(l, N - 1 - (r + rl - 1) + N + 1);

  if (lcs >= ll)
    return true;
  else
    return false;
}

void init()
{
  getline(cin, line);
  N = line.size();
  string inputline(N * 2 + 2, ' ');
  for (int i = 0; i < N; ++i)
    inputline[i] = line[i];
  inputline[N] = '#';
  for (int i = 0; i < N; ++i)
    inputline[N + 1 + i] = line[N - 1 - i];
  inputline[N * 2 + 1] = '!';

  sa = new SuffixArray(inputline);

  for (int i = 0; i <= N; ++i)
    firstAppear[i] = 99999999;

  int nowPosi = 0;
  for (int sufLen = 1; sufLen <= N; ++sufLen)
  {
    if (nowPosi + sufLen - 1 >= N) break;
    bool found = false;
    while (true)
    {
      if (isSubStrSame(nowPosi, sufLen, N - sufLen, sufLen))
      {
        found = true;
        firstAppear[sufLen] = nowPosi;
        break;
      }
      nowPosi++;
      if (nowPosi + sufLen - 1 >= N) break;
    }
    if (!found) break;
  }
}

int getMaxMidLen(int nowmid)
{
  int l = 0;
  int r = N;
  while (l < r)
  {
    int mid = (l + r) / 2 + 1;

    int lStart = nowmid - mid;
    int rStart = nowmid + 1;
    if (isSubStrSame(lStart, mid, rStart, mid))
      l = mid;
    else
      r = mid - 1;
  }

  return l;
}


void deal()
{
  int ans = 0;
  vector<pair<int, int> > ansDetail;
  for (int mid = 0; mid < N; ++mid)
  {
    int maxMidLen = getMaxMidLen(mid);

    int leftSize = mid - maxMidLen;
    int rightSize = N - maxMidLen * 2 - 1 - leftSize;
    vector<pair<int, int> > detail;

    int l = 0;
    int r = min(leftSize, rightSize);
    while (l < r)
    {
      int nowL = (l + r) / 2 + 1;
      int posi = firstAppear[nowL];
      if (posi + nowL - 1 <= leftSize - 1)
        l = nowL;
      else
        r = nowL - 1;
    }

    int nowAns = l;
    int leftApp = firstAppear[nowAns];

    if (nowAns > 0)
      detail.push_back(make_pair(leftApp , nowAns));
    detail.push_back(make_pair(leftSize, 1 + 2 * maxMidLen));
    if (nowAns > 0)
      detail.push_back(make_pair(N - nowAns, nowAns));

    nowAns = 1 + 2 * nowAns + 2 * maxMidLen;

    if (nowAns > ans)
    {
      ans = nowAns;
      ansDetail = detail;
    }
  }

  cout << ansDetail.size() << endl;
  for (int i = 0; i < ansDetail.size(); ++i)
    cout << ansDetail[i].first + 1 << " " << ansDetail[i].second << endl;
}

int main()
{
  init();
  deal();


  return 0;
}
