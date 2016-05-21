#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1010;
const int INF = 0x3f3f3f3f;
set<int> A, B;
vector<int> res;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int a, b, v;
    while(~scanf("%d %d", &a, &b), a + b) {
        rep(i, a + b) {
            scanf("%d", &v);
            if(i < a) A.insert(v);
            else B.insert(v);
        }
        for(set<int>::iterator i = A.begin(); i != A.end(); ++i) {
            if(B.find(*i) == B.end()) res.pb(*i);
        }
        int n = sz(res);
        if(!n) { puts("NULL"); continue; }
        rep(i, n) printf("%d ", res[i]);
        putchar('\n');
        A.clear(), B.clear(), res.clear();
    }
    return 0;
}
