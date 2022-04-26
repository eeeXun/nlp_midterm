#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> longituds(string s)
{
  int n=int(s.size());
  vector<int> len(int(s.size()));
  string s1=s;
  reverse(s1.begin(),s1.end());
  s=s1+"#"+s;
  int j=-1;
  vector<int> anterior(int(s.size()));
  anterior[0]=-1;
  for (int i=1;i<int(s.size())-2;i++) {
    while (j!=-1 and s[i]!=s[j+1]) j=anterior[j];
    if (s[j+1]==s[i]) j++;
    if (i>n)
      while (j+1>2*n-i-1/*n-(i-(n+1)+2)*/) j=anterior[j];
    anterior[i]=j;
  }
  for (int i=0;i<n-2;i++)
    len[i]=anterior[n+1+i]+1;
  return len;
}

vector<int> palindromos(string s)
{
  vector<int> r(int(s.size()));
  r[0]=0;
  int imax=0;
  for (int i=1;i<int(s.size());i++) {
    if (i>=imax+r[imax] or i+r[imax-(i-imax)]>=imax+r[imax]) {
      r[i]=0;
      if (i<imax+r[imax])
	r[i]=imax+r[imax]-i;
      while (i-r[i]>0 and i+r[i]<int(s.size())-1 and s[i-r[i]-1]==s[i+r[i]+1])
	r[i]++;
      imax=i;
    } else {
      r[i]=r[imax-(i-imax)];
    }
  }
  return r;
}

vector<int> padre;
vector<pair<int,int> > maxright;
vector<pair<int,int> > maxleft;
vector<pair<int,int> > valor;
int n;

void computapadre(int inf,int sup,int p)
{
  if (inf>sup) return;
  int med=(inf+sup)/2;
  padre[med]=p;
  computapadre(inf,med-1,med);
  computapadre(med+1,sup,med);
}


void computamaxims()
{
  maxright=vector<pair<int,int> > (n,pair<int,int> (-1,0));
  maxleft=vector<pair<int,int> > (n,pair<int,int> (-1,0));
  for (int i=n-1;i>=0;i--) {
    int p=i;
    while (padre[p]!=-1) {
      pair<int,int> maxim=max(maxleft[p],max(maxright[p],valor[p]));
      if (padre[p]<p)
	maxright[padre[p]]=maxim;
      else
	maxleft[padre[p]]=maxim;
      p=padre[p];
    }
  }
}

pair<int,int> maximentre(int i1,int i2)
{
  int inf=0;int sup=n-1;int med=(inf+sup)/2;
  while (med<i1 or i2<med) {
    if (med<i1) inf=med+1;
    else sup=med-1;;
    med=(inf+sup)/2;
  }
  pair<int,int> maxim=valor[med];
  {
    int previ1=i1;
    while (i1<med) {
      if (previ1<=i1) maxim=max(maxim,max(valor[i1],maxright[i1]));
      previ1=i1;
      i1=padre[i1];
    }
  }
  {
    int previ2=i2;
    while (med<i2) {
      if (i2<=previ2) maxim=max(maxim,max(valor[i2],maxleft[i2]));
      previ2=i2;
      i2=padre[i2];
    }
  }
  return maxim;
} 

pair<int,int> maximencabut(int i1,int i2)
{
  pair<int,int> maxim(-1,0);
  int inf=i1;
  int sup=(i1+i2)/2;
  while (inf<=sup) {
    int med=(inf+sup)/2;
    int medd=i2-(med-i1);
    pair<int,int> val=maximentre(med,medd);
    pair<int,int> valreal=val;
    valreal.first=min(valreal.first,med-i1);
    maxim=max(maxim,valreal);
    if (valreal.first<val.first)
      inf=med+1;
    else
      sup=med-1;
  }
  return maxim;
}

int main()
{
  string s;
  cin>>s;
  n=int(s.size());
  vector<int> len=longituds(s);
  vector<int> r=palindromos(s);
  valor=vector<pair<int,int> > (n);
  for (int i=0;i<n;i++)
    valor[i]=pair<int,int> (r[i],i);
  padre=vector<int> (n);
  computapadre(0,n-1,-1);
  computamaxims();
  pair<int,int> maxpal=maximentre(0,n-1);
  int maxlen=2*maxpal.first+1;
  vector<pair<int,int> > sol(1,pair<int,int>
			     (maxpal.second-maxpal.first,maxlen));
  for (int i=0;i<n-2;i++) {
    if (len[i]>0) {
      pair<int,int> encabut=maximencabut(i+1,n-1-len[i]);
      int lenact=2*len[i]+2*encabut.first+1;
      if (lenact>maxlen) {
	sol=vector<pair<int,int> > (3);
	sol[0]=pair<int,int> (i-len[i]+1,len[i]);
	sol[1]=pair<int,int> (encabut.second-encabut.first,2*encabut.first+1);
	sol[2]=pair<int,int> (n-len[i],len[i]);
	maxlen=lenact;
      }
    }
  }
  cout<<int(sol.size())<<endl;
  for (int i=0;i<int(sol.size());i++)
    cout<<sol[i].first+1<<" "<<sol[i].second<<endl;
}
