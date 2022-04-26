    struct hash<variant<_Types...>>
    : private __detail::__variant::_Variant_hash_base<
 variant<_Types...>, std::index_sequence_for<_Types...>>,
      public __variant_hash_call_base<_Types...>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = variant<_Types...>;
    };

  template<>
    struct hash<monostate>
    {
      using result_type [[__deprecated__]] = size_t;
      using argument_type [[__deprecated__]] = monostate;

      size_t
      operator()(const monostate&) const noexcept
      {
 constexpr size_t __magic_monostate_hash = -7777;
 return __magic_monostate_hash;
      }
    };

  template<typename... _Types>
    struct __is_fast_hash<hash<variant<_Types...>>>
    : bool_constant<(__is_fast_hash<_Types>::value && ...)>
    { };


}
# 134 "/usr/include/c++/11.2.0/x86_64-pc-linux-gnu/bits/stdc++.h" 2 3
# 2 "data/654.cpp" 2
# 36 "data/654.cpp"

# 36 "data/654.cpp"
using namespace std;

typedef long long int ll;
typedef unsigned long long int lu;

char s[((int)(2e5+10))], str[((int)(2e5+10))];

int pal[((int)(2e5+10))];

void manach(char *str){
    int i;
    for(i = 0; str[i]!='\0'; i++){
        s[2*i] = str[i];
        s[2*i + 1] = '#';
    }
    s[2*i-1] = '\0';

    pal[0] = 0;
    int now = 0;
    for(i = 1; s[i]!='\0'; i++){
        pal[i] = max(0,min(pal[now]-(i-now),pal[now-(i-now)])) + 1;
        while(i-pal[i]>=0 && s[i+pal[i]]==s[i-pal[i]]) pal[i]++;
        pal[i]--;
        if(pal[i]>pal[now]) now = i;
    }
    for(i = 0; s[i]!='\0'; i++){
        if(s[i]=='#') pal[i] = (pal[i]+1)/2;
        else pal[i] = pal[i]/2;
    }

}




int prefx[((int)(2e5+10))];
void kmp(char *s){
    prefx[0] = -1;
    int now;
    for(int i = 1; s[i]!='\0'; i++){
        now = prefx[i-1];
        while(now!=-1 && s[i]!=s[now+1]) now = prefx[now];
        if(s[i]==s[now+1]) prefx[i] = now+1;
        else prefx[i] = -1;
    }
}

vector < int > v[((int)(2e5+10))];


int main()
{
    int i, n, j, l, ans,x, y, keep, tmp;
    while(0){
        scanf("%d",&i);
        cout<<(char)i;
    }

    scanf("%s",str);
    n = strlen(str);
    manach(str);
    for(i = 0; str[i]!='\0'; i++){
        pal[i] = pal[i*2];
        v[i-pal[i]].push_back(i+pal[i]);
    }



    for(i = 0; i<n; i++) s[i] = str[n-1-i];
    s[n] = '#';
    for(i = 0; i<n; i++) s[i+n+1] = str[i];
    s[2*n+1] = '\0';

    kmp(s);
    l = 0;

    keep = ans = 0;
    for(i = 0; i<n; i++){

        for(j = 0; j<v[i].size(); j++){
            tmp = v[i][j]-i+1+2*min(prefx[keep]+1,n-1-v[i][j]);
            if(tmp>ans){
                x = i;
                y = v[i][j];
                ans = tmp;


            }
        }

        if(prefx[l+n+1]>prefx[keep]){
            keep = l+n+1;
        }
        l++;
    }


    keep = 0;
    for(i = 0; i<x; i++){
        if(prefx[i+n+1]>prefx[keep]) keep = i+n+1;
    }

    if(keep==0){
        printf("1\n");
        printf("%d %d\n",x+1,y-x+1);
    }
    else{
        printf("3\n");
        if(prefx[keep]+1>n-1-y) printf("%d %d\n",keep-n-1-(n-1-y)+2,n-1-y);
        else printf("%d %d\n",keep-n-1-prefx[keep]+1,prefx[keep]+1);
        printf("%d %d\n",x+1,y-x+1);
        if(prefx[keep]+1>n-1-y) printf("%d %d\n",n-(n-1-y)+1,n-1-y);
        else printf("%d %d\n",n-prefx[keep],prefx[keep]+1);
    }
    return 0;
}
