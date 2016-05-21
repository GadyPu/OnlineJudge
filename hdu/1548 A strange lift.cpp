#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::vector;
using std::queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int Max_N = 210;
const int dx[] = { -1, 1 };
typedef unsigned long long ull;
bool vis[Max_N];
int N, A, B, arr[Max_N];
struct Node {
    int x, s;
    Node(int i = 0, int j = 0) :x(i), s(j) {}
};
void bfs() {
    cls(vis, 0);
    queue<Node> que;
    que.push(Node(A, 0));
    vis[A] = true;
    while (!que.empty()) {
        Node tp = que.front(); que.pop();
        if (tp.x == B) { printf("%d\n", tp.s); return; }
        rep(i, 2) {
            int nx = dx[i] * arr[tp.x] + tp.x;
            if (nx < 0 || nx > N || vis[nx]) continue;
            que.push(Node(nx, tp.s + 1));
            vis[nx] = true;
        }
    }
    puts("-1");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%d", &N) && N) {
        scanf("%d %d", &A, &B);
        rep(i, N) scanf("%d", &arr[i + 1]);
        bfs();
    }
    return 0;
}
