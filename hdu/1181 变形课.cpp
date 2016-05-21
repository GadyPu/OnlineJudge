#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::pair;
using std::queue;
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
const int N = 26;
bool vis[N], G[N][N];
typedef unsigned long long ull;
void bfs(int s) {
    cls(vis, false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        rep(i, N) {
            if (!G[v][i] || vis[i]) continue;
            q.push(i);
            vis[i] = true;
        }
    }
    puts(vis['m' - 'a'] ? "Yes." : "No.");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char buf[40];
    while (~scanf("%s", buf)) {
        if (buf[0] != '0') {
            G[buf[0] - 'a'][buf[strlen(buf) - 1] - 'a'] = true;
        } else {
            bfs(1);
            cls(G, false);
        }
    }
    return 0;
}
