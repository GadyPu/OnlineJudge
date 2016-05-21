#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::string;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
typedef unsigned long long ull;
struct TopSort {
    int k, inq[N];
    map<string, int> rec;
    inline void init() {
        k = 0;
        rec.clear(), cls(inq, 0);
    }
    inline void built(int m) {
        int  a;
        char str1[20], str2[20];
        rep(i, m) {
            scanf("%s %s", str1, str2);
            if (rec.find(str1) == rec.end()) rec[str1] = k++;
            if (rec.find(str2) == rec.end()) rec[str2] = k++;
            a = rec[str2];
            inq[a]++;
        }
    }
    inline void solve() {
        int ans = 0;
        rep(i, sz(rec)) {
            if (!inq[i]) ans++;
        }
        puts(ans == 1 ? "Yes" : "No");
    }
}work;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n) && n) {
        work.init();
        work.built(n);
        work.solve();
    }
    return 0;
}
