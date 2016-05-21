#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::set;
using std::map;
using std::pair;
using std::vector;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 100010;
typedef unsigned long long ull;
int main() {
#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w+",stdout);
#endif
    int t;
    ull ret;
    scanf("%d",&t);
    while(t--) {
        int f = 1, ans = 0;;
        scanf("%lld",&ret);
        while(ret) {
            if(f) {
                if(ret & 1) ans++, f = 0;
            } else if(!(ret & 1)) f = 1;
            ret >>= 1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
