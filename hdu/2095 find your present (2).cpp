/******************************** hash********************************/
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1000007;
const int INF = 0x3f3f3f3f;
int arr[N];
struct Hash_Set {
    int tot, num[N], head[N], next[N];
    inline void init(int n) {
        tot = 0;
        rep(i, n + 1) head[i] = -1;
    }
    inline void insert(int val) {
        int u = val % N;
        num[tot] = u, next[tot] = head[u], head[u] = tot++;
    }
    inline bool find(int val) {
        int tot = 0, u = val % N;
        for(int i = head[u]; ~i; i = next[i]) {
            if(num[i] == val) tot++;
            if(tot >= 2) return true;
        }
        return false;
    }
}hash;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while(~scanf("%d", &n), n) {
        hash.init(n);
        rep(i, n) {
            scanf("%d", &arr[i]);
            hash.insert(arr[i]);
        }
        rep(i, n) {
            if(!hash.find(arr[i])) {
                printf("%d\n", arr[i]);
                break;
            }
        }
    }
    return 0;
}
/******************************** stl ********************************/
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::min;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 1000007;
const int INF = 0x3f3f3f3f;
map<int, int> A;
map<int, int>::iterator it;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v;
    while(~scanf("%d", &n), n) {
        rep(i, n) {
            scanf("%d", &v);
            A[v]++;
        }
        for(it = A.begin(); it != A.end(); ++it) {
            if(it->second == 1) {
                printf("%d\n", it->first);
                break;
            }
        }
        A.clear();
    }
    return 0;
}
