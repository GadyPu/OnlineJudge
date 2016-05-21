#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::pair;
using std::swap;
using std::queue;
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
const int N = 1000007;
const int MOD = 100000007;
const int INF = 0x3f3f3f3f;
typedef long long ll;
struct Node {
    int s;
    int mat[4][8];
    inline bool operator==(const Node &x) const {
        rep(i, 4) {
            rep(j, 8) {
                if(mat[i][j] != x.mat[i][j]) return false;
            }
        }
        return true;
    }
    inline int hash() const {
        ll ret = 0, k = 1;
        rep(i, 4) {
            rep(j, 8) {
                ret = (ret + k * mat[i][j]) % MOD;
                k <<= 1;
            }
        }
        return (int)ret;
    }
    inline void read() {
        rep(i, 4) {
            mat[i][0] = 0;
            rep(j, 7) {
                scanf("%d", &mat[i][j + 1]);
            }
        }
        rep(i, 4) {
            rep(j, 8) {
                int v = mat[i][j];
                if(1 == v % 10) {
                    swap(mat[i][j], mat[v / 10 -1][0]);
                }
            }
        }
    }
}start, goal;
struct Hash_Set {
    int tot, A[N], head[N], next[N];
    inline void init() {
        tot = 0, cls(head, -1);
    }
    inline bool insert(const int val) {
        int u = val % N;
        for(int i = head[u]; ~i; i = next[i]) {
            if(A[i] == val) return false;
        }
        A[tot] = val, next[tot] = head[u]; head[u] = tot++;
        return true;
    }
}hash;
void bfs() {
    hash.init();
    queue<Node> q;
    q.push(start);
    hash.insert(start.hash());
    while(!q.empty()) {
        Node x = q.front(); q.pop();
        rep(i, 4) {
            rep(j, 8) {
                if(x.mat[i][j]) continue;
                Node t = x;
                int x1 = 0, y1 = 0, val = x.mat[i][j - 1] + 1;
                if(1 == val || 8 == val % 10) continue;
                rep(k, 4) {
                    rep(l, 8) {
                        if(val == x.mat[k][l]) {
                            x1 = k, y1 = l; k = 4;
                            break;
                        }
                    }
                }
                t.s = x.s + 1;
                swap(t.mat[i][j], t.mat[x1][y1]);
                if(t == goal) {
                    printf("%d\n", t.s);
                    return;
                }
                val = t.hash();
                if(!hash.insert(val)) continue;
                q.push(t);
            }
        }
    }
    puts("-1");
}
void solve() {
    start.read();
    rep(i, 4) {
        rep(j, 7) {
            goal.mat[i][j] = (i + 1) * 10 + (j + 1);
        }
        goal.mat[i][7] = 0;
    }
    if(start == goal) {
        puts("0");
        return;
    }
    bfs();
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while(t--) {
        solve();
    }
    return 0;
}
