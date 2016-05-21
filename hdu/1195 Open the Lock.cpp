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
using std::swap;
using std::sort;
using std::map;
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
const int N = 10010;
typedef unsigned long long ull;
bool vis[N];
int start, end;
struct Node {
    int v, s;
    Node(int i = 0, int j = 0) :v(i), s(j) {}
};
inline void calc_1(int *arr, int v) {
    int i, t, j = 0;
    do arr[j++] = v % 10; while (v /= 10);
    for (i = 0, --j; i < j; i++, j--) {
        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}
inline int calc_2(int *arr) {
    int sum = 0;
    rep(i, 4) sum = sum * 10 + arr[i];
    return sum;
}
inline void calc_3(queue<Node> &q, int k, int s) {
    if (!vis[k]) {
        q.push(Node(k, s + 1));
        vis[k] = true;
    }
}
int bfs() {
    int v, k, tmp[10];
    cls(vis, false);
    queue<Node> q;
    q.push(Node(start, 0));
    vis[start] = true;
    while (!q.empty()) {
        Node t = q.front(); q.pop();
        if (t.v == end) return t.s;
        calc_1(tmp, t.v);
        rep(i, 4) {
            v = tmp[i];
            if (v + 1 == 10) tmp[i] = 1;
            else tmp[i] = v + 1;
            k = calc_2(tmp);
            calc_3(q, k, t.s);
            tmp[i] = v;
            if (v - 1 == 0) tmp[i] = 9;
            else tmp[i] = v - 1;
            k = calc_2(tmp);
            calc_3(q, k, t.s);
            tmp[i] = v;
        }
        rep(i, 3) {
            calc_1(tmp, t.v);
            swap(tmp[i], tmp[i + 1]);
            k = calc_2(tmp);
            calc_3(q, k, t.s);
        }
    }
    return 0;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &start, &end);
        printf("%d\n", bfs());
    }
    return 0;
}
