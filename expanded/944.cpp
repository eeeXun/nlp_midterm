

# 5 "data/944.cpp"
using namespace std;

char s[100010],
        t[200020];
int mrl[200020],
        lp[100010];

int m = 0,
    n = 0,
    rMax = 0,
    curMax = 0,
    lx = 0,
    rx = 0,
    ll = 0,
    rl = 0,
    mx = 0,
    ml = 0;

void manacher() {
    for(int i = 0, j = 0, pos = 0, l = 0; i<m; ++i) {
        if(i>=j) {
            l = 0;
        }
        else {
            l = min(j-i, mrl[2*pos-i]);
        }

        while(i+l+1<m && i-l-1>=0 && t[i+l+1] == t[i-l-1]) {
            ++l;
        }

        mrl[i] = l;
        if(i+l>j) {
            pos = i;
            j = i+l;
        }
    }
}

void calPos() {
    lp[0] = -1;
    int i = 0,
        len = 1,
        hash1 = 0,
        hash2 = 0,
  flag = 1,
  p = 131;

    while(i+len<=n && len<=n/2) {
     if(flag) {
      hash1 = 131*hash1+s[i+len-1];
      hash2 = hash2*131+s[n-len];
  }
  else {
      hash1 = hash1*131+s[i+len-1]-s[i-1]*p;
  }

        if(hash1 == hash2) {
            lp[len] = i;
            ++len;
            flag = 1;
            p *= 131;
        }
        else {
            flag = 0;
            ++i;
        }
    }

    for(int j = len; j<=n; ++j) {
        lp[j] = -1;
    }
}

void calLen(int i) {
    int len = mrl[2*i+1],
        suffix = n-(i+len/2)-1,
        prefix = i-len/2;

    int le = 1,
        ri = min(suffix, prefix);

    int tmp = 0,
        idx = 0;
    while(le<=ri) {
        int mid = (ri+le)/2;
        if(lp[mid] == -1 || lp[mid]+mid>i-len/2) {
            ri = mid-1;
        }
        else {
            tmp = mid;
            idx = lp[mid];
            le = mid+1;
        }
    }

    int curLen = 2*tmp+len;
    if(curLen>curMax) {
        curMax = curLen;
        lx = idx;
        ll = tmp;
        rx = n-tmp;
        rl = tmp;
        mx = i-len/2;
        ml = len;
    }
}

int main() {
    scanf("%s", s);
    n = strlen(s);

    for(int i = 0; i<n; ++i) {
        t[m] = '#';
        t[m+1] = s[i];
        m += 2;
    }
    t[m] = '#';
    ++m;

    manacher();

    if(n == 1) {
        printf("1\n");
        printf("1 1\n");
        return 0;
    }
    calPos();

    for(int i = 0; i<n; ++i) {
        calLen(i);
    }

    int cnt = 0;
    if(ll) {
        ++cnt;
    }
    if(rl) {
        ++cnt;
    }
    if(ml) {
        ++cnt;
    }

    printf("%d\n", cnt);
    if(ll) {
        printf("%d %d\n", lx+1, ll);
    }
    if(ml) {
        printf("%d %d\n", mx+1, ml);
    }
    if(rl) {
        printf("%d %d\n", rx+1, rl);
    }

    return 0;
}
