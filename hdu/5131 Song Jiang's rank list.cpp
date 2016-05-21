#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
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
using std::string;
using std::multiset;
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
const int N = 210;
typedef unsigned long long ull;
map<string, int> A;
map<int, set<string> >B;
struct Node {
    int val;
    string name;
    inline bool operator<(const Node &a) const {
        return val == a.val ? name < a.name : val > a.val;
    }
}rec[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    std::ios::sync_with_stdio(false);
    int n, m;
    string buf;
    while (~scanf("%d", &n) && n) {
        A.clear(), B.clear();
        rep(i, n) {
            cin >> rec[i].name >> rec[i].val;
            A[rec[i].name] = rec[i].val;
            B[rec[i].val].insert(rec[i].name);
        }
        sort(rec, rec + n);
        rep(i, n) cout << rec[i].name << " " << rec[i].val << endl;
        cin >> m;
        while (m--) {
            cin >> buf;
            int v, ans1 = 1, ans2 = 1;
            v = A[buf];
            tr(A, i) if (i->second > v) ans1++;
            tr(B[v], i) if (*i < buf) ans2++;
            if (1 == ans2) printf("%d\n", ans1);
            else printf("%d %d\n", ans1, ans2);
        }
    }
    return 0;
}
