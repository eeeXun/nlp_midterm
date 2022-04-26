




      template<size_t _Np, typename _Vp>
 friend constexpr decltype(auto)
 __detail::__variant::__get(_Vp&& __v) noexcept;

      template<typename _Vp>
 friend void*
 __detail::__variant::__get_storage(_Vp&& __v) noexcept;







      template<typename... _Tp> friend constexpr bool operator <(const variant<_Tp...>& __lhs, const variant<_Tp...>& __rhs);
      template<typename... _Tp> friend constexpr bool operator <=(const variant<_Tp...>& __lhs, const variant<_Tp...>& __rhs);
      template<typename... _Tp> friend constexpr bool operator ==(const variant<_Tp...>& __lhs, const variant<_Tp...>& __rhs);
      template<typename... _Tp> friend constexpr bool operator !=(const variant<_Tp...>& __lhs, const variant<_Tp...>& __rhs);
      template<typename... _Tp> friend constexpr bool operator >=(const variant<_Tp...>& __lhs, const variant<_Tp...>& __rhs);
      template<typename... _Tp> friend constexpr bool operator >(const variant<_Tp...>& __lhs, const variant<_Tp...>& __rhs);


    };

  template<size_t _Np, typename... _Types>
    constexpr variant_alternative_t<_Np, variant<_Types...>>&
    get(variant<_Types...>& __v)
    {
      static_assert(_Np < sizeof...(_Types),
      "The index must be in [0, number of alternatives)");
      if (__v.index() != _Np)
 __throw_bad_variant_access(__v.valueless_by_exception());
      return __detail::__variant::__get<_Np>(__v);
    }

  template<size_t _Np, typename... _Types>
    constexpr variant_alternative_t<_Np, variant<_Types...>>&&
    get(variant<_Types...>&& __v)
    {
      static_assert(_Np < sizeof...(_Types),
      "The index must be in [0, number of alternatives)");
      if (__v.index() != _Np)
 __throw_bad_variant_access(__v.valueless_by_exception());
      return __detail::__variant::__get<_Np>(std::move(__v));
    }

  template<size_t _Np, typename... _Types>
    constexpr const variant_alternative_t<_Np, variant<_Types...>>&
    get(const variant<_Types...>& __v)
    {
      static_assert(_Np < sizeof...(_Types),
      "The index must be in [0, number of alternatives)");
      if (__v.index() != _Np)
 __throw_bad_variant_access(__v.valueless_by_exception());
      return __detail::__variant::__get<_Np>(__v);
    }

  template<size_t _Np, typename... _Types>
    constexpr const variant_alternative_t<_Np, variant<_Types...>>&&
    get(const variant<_Types...>&& __v)
    {
      static_assert(_Np < sizeof...(_Types),
      "The index must be in [0, number of alternatives)");
      if (__v.index() != _Np)
 __throw_bad_variant_access(__v.valueless_by_exception());
      return __detail::__variant::__get<_Np>(std::move(__v));
    }

  template<typename _Result_type, typename _Visitor, typename... _Variants>
    constexpr decltype(auto)
    __do_visit(_Visitor&& __visitor, _Variants&&... __variants)
    {
      constexpr auto& __vtable = __detail::__variant::__gen_vtable<
 _Result_type, _Visitor&&, _Variants&&...>::_S_vtable;

      auto __func_ptr = __vtable._M_access(__variants.index()...);
      return (*__func_ptr)(std::forward<_Visitor>(__visitor),
      std::forward<_Variants>(__variants)...);
    }

  template<typename _Visitor, typename... _Variants>
    constexpr __detail::__variant::__visit_result_t<_Visitor, _Variants...>
    visit(_Visitor&& __visitor, _Variants&&... __variants)
    {
      if ((__variants.valueless_by_exception() || ...))
 __throw_bad_variant_access("std::visit: variant is valueless");

      using _Result_type
 = __detail::__variant::__visit_result_t<_Visitor, _Variants...>;

      using _Tag = __detail::__variant::__deduce_visit_result<_Result_type>;

      if constexpr (sizeof...(_Variants) == 1)
 {
   constexpr bool __visit_rettypes_match = __detail::__variant::
     __check_visitor_results<_Visitor, _Variants...>(
       std::make_index_sequence<
         std::variant_size<remove_reference_t<_Variants>...>::value>());
   if constexpr (!__visit_rettypes_match)
     {
       static_assert(__visit_rettypes_match,
     "std::visit requires the visitor to have the same "
     "return type for all alternatives of a variant");
       return;
     }
   else
     return std::__do_visit<_Tag>(
       std::forward<_Visitor>(__visitor),
       std::forward<_Variants>(__variants)...);
 }
      else
 return std::__do_visit<_Tag>(
   std::forward<_Visitor>(__visitor),
   std::forward<_Variants>(__variants)...);
    }
# 1787 "/usr/include/c++/11.2.0/variant" 3
  template<bool, typename... _Types>
    struct __variant_hash_call_base_impl
    {
      size_t
      operator()(const variant<_Types...>& __t) const
      noexcept((is_nothrow_invocable_v<hash<decay_t<_Types>>, _Types> && ...))
      {
 size_t __ret;
 __detail::__variant::__raw_visit(
   [&__t, &__ret](auto&& __t_mem) mutable
   {
     using _Type = __remove_cvref_t<decltype(__t_mem)>;
     if constexpr (!is_same_v<_Type,
                __detail::__variant::__variant_cookie>)
       __ret = std::hash<size_t>{}(__t.index())
        + std::hash<_Type>{}(__t_mem);
     else
       __ret = std::hash<size_t>{}(__t.index());
   }, __t);
 return __ret;
      }
    };

  template<typename... _Types>
    struct __variant_hash_call_base_impl<false, _Types...> {};

  template<typename... _Types>
    using __variant_hash_call_base =
    __variant_hash_call_base_impl<(__poison_hash<remove_const_t<_Types>>::
       __enable_hash_call &&...), _Types...>;

  template<typename... _Types>
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
# 17 "data/742.cpp" 2


# 18 "data/742.cpp"
using namespace std;
# 121 "data/742.cpp"
template< class T, class first > inline bool checkbit(T a, first pos) { T t=1;return ((a&(t<<pos))>0); }
template< class T, class first > inline T setbit(T a, first pos) { T t=1;return (a|(t<<pos)); }
template< class T, class first > inline T resetbit(T a, first pos) { T t=1;return (a&(~(t<<pos))); }
template< class T, class first > inline T togglebit(T a, first pos) { T t=1;return (a^(t<<pos)); }
# 188 "data/742.cpp"
int ar[300007];

char ss[300007];


struct Manacher {
    char text[300007*2];
    int p[300007*2];
    int lcp,lcp_cen;
    int tot;
    vector< pair<int,int> > pal;

    void init() {
        pal.clear();
        lcp=0;
        tot=0;
        memset(p,0,sizeof p);
    }

    void generate(char *s) {
        init();
        int len = 0 , i=0 ;
        text[len++] = '^';
        while(s[i]) text[len++]= '#' , text[ len++ ] = s[i++] ;
        text[len++]= '#';
        text[len++]= '$';
        int c = 0;
        int r = 0;
        for(i=1; i<len-1; i++) {
            int j = (c<<1)-i;
            p[i] = (r>i)?min(r-i,p[j]):0;
            while(text[i+1+p[i]]==text[i-1-p[i]]) p[i]++;
            if(i+p[i]>r) c=i,r=i+p[i];
        }
        for(i=1; i<len-1; i++) {



            if(p[i]>lcp) {
                lcp = p[i];
                lcp_cen = i;
            }
# 238 "data/742.cpp"
        }

        for(int i=2;i<len-1;i+=2){

            ar[i/2] = p[i];
        }

    }

    void BUG(char *s) {
        for(int i=0; i<pal.size(); i++) {
            for(int j=pal[i].first; j<pal[i].second; j++) {
                cout << s[j];
            }
            cout << endl;
        }
    }

}man;

char ms[300007];

int n;

int mil[300007];

void z_function(int *z,char *s) {
    int len = strlen(s);
    for(int i=0;i<=len;i++) z[i] = 0;
    for (int i = 1, l = 0, r = 0; i < len; ++i) {
        if (i <= r) z[i] = min (r - i + 1, z[i - l]);
        while ( i + z[i] < len && s[z[i]] == s[i + z[i]] ) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    z[0] = len;
    int id = 1;
    for(int i=n+1;i<=len-1;i++) {
        mil[id++] = z[i];
    }
}

int zz[300007];

struct Seg_Point_update_range_Max {

    int tree[2*300007];
    int n;

    void init(int *ar) {
        for(int i=n;i>=1;i--) tree[i-1+n] = ar[i];
        for(int i=n-1;i>=1;i--) tree[i] = (tree[(i<<1)]>tree[(i<<1)|1]?tree[(i<<1)]:tree[(i<<1)|1]);
    }

    void update(int idx,int val) {
        idx--;
        for(tree[idx+=n]=val; idx>1; idx>>=1) {
            tree[idx>>1] = (tree[idx]>tree[idx^1]?tree[idx]:tree[idx^1]);
        }
    }


    int query(int x,int y) {
        int ret = 0;
        x--;
        for(x+=n,y+=n; x<y; x>>=1,y>>=1) {
            if(x&1) ret=(ret>tree[x]?ret:tree[x]),x++;
            if(y&1) --y,ret=(ret>tree[y]?ret:tree[y]);
        }
        return ret;
    }

} smax;


int main() {
    scanf("%s",ss);
    man.init();
    man.generate(ss);
    n=strlen(ss);
    for(int i=1;i<=n;i++) {
        if(ar[i]==n) {
            cout << 1 << endl;
            cout << 1 << " " << n << endl;
            return 0;
        }
    }

    int id=n-1;
    for(int i=0;i<=n-1;i++) {
        ms[i] = ss[id--];
    }
    ms[n] = '#';

    for(int i=0;i<=n-1;i++) {
        ms[n+1+i] = ss[i];
    }

    ms[n+1+n] = 0;

    z_function(zz,ms);

    smax.n = n;
    smax.init(mil);

    int ret = -1;
    int majpos = -1;
    int sufflen = -1;
    int majlen = 0;

    for(int i=2;i<=n-1;i++) {
        int low = i;
        int high = i+(ar[i]/2);
        if(high==n) high--;
        int pos = -1;
        while( low<=high ) {
            int mid = (low+high)>>1;
            int lt = (i-(mid-i));
            if(lt-1 < 1) {
                high = mid-1;
                continue;
            }

            int v = smax.query(1,lt-1);
            if(v>0) pos = mid, low = mid+1;
            else high = mid-1;
        }

        if(pos==-1) continue;

        int lpos = i-(pos-i);
        low = 1;
        high = (n-pos<lpos?n-pos:lpos);
        int mxlen = 0;

        while(low<=high) {
            int mid = (low+high)>>1;
            if(lpos-mid<1) {
                high = mid-1;
                continue;
            }
            int mx = smax.query(1,lpos-mid);
            if(mx>=mid) mxlen = mid , low=mid+1;
            else high = mid-1;
        }

        if(mxlen) {
            int tot = (pos-i)*2+1 + mxlen*2;

            if(ret<tot) {
                ret = tot;
                majpos = i-(pos-i);
                majlen = (pos-i)*2+1;
                sufflen = mxlen;
            }
        }

    }
    int flag = 0;
    int mxsuff = 0;
    int spos = -1;
    for(int i=1;i<=n;i++) {
        int e=i+(ar[i]/2);
        if(e==n && ar[i]>=ret) {
            if(mxsuff<ar[i]) {
                mxsuff=ar[i];
                spos = i;
            }
        }
    }

    int midmx = 0;

    for(int i=1;i<=n;i++)
    {
        if(ar[i]>=ret)
        {
            ret = ar[i];
            midmx = i;
        }
    }

    if(midmx)
    {

        cout << 1 << endl;
        cout << (midmx-(ret/2)) << " " << ret << endl;
        return 0;
    }


    if(spos!=-1) {
        cout << 1 << endl;
        cout << (spos-(n-spos)) << " " << mxsuff << endl;
        return 0;
    }




    cout << 3 << endl;
    for(int i=1;i<=n;i++) {
        if(mil[i]>=sufflen ) {
            cout << i << " " << sufflen << endl;
            break;
        }
    }
    cout << majpos << " " << majlen << endl;
    cout << (n-sufflen+1) << " " << sufflen << endl;


    return 0;
}
