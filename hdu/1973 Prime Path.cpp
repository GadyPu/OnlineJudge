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
using std::queue;
using std::vector;
using std::reverse;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int Max_N = 10010;
typedef unsigned long long ull;
int start, end;
namespace work {
    struct Node {
        int v, s;
        Node(int i = 0, int j = 0) :v(i), s(j) {}
    };
    bool vis[Max_N], Prime[Max_N];
    inline bool isPrime(int n) {
        for (int i = 2; (ull)i * i <= n; i++) {
            if (0 == n % i) return false;
        }
        return n != 1;
    }
    inline void init() {
        for (int i = 1; i < Max_N; i++) {
            Prime[i] = isPrime(i);
        }
    }
    inline void bfs() {
        char buf[10], str[10];
        cls(vis, false);
        queue<Node> que;
        que.push(Node(start, 0));
        vis[start] = true;
        while (!que.empty()) {
            Node tmp = que.front(); que.pop();
            if (tmp.v == end) { printf("%d\n", tmp.s); return; }
            sprintf(buf, "%d", tmp.v);
            reverse(buf, buf + 4);
            for (int i = 0; buf[i] != '\0'; i++) {
                rep(j, 10) {
                    strcpy(str, buf);
                    str[i] = j + '0';
                    reverse(str, str + 4);
                    int v = atoi(str);
                    if (vis[v] || !Prime[v]) continue;
                    que.push(Node(v, tmp.s + 1));
                    vis[v] = true;
                }
            }
        }
        puts("Impossible");
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    work::init();
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &start, &end);
        work::bfs();
    }
    return 0;
}
