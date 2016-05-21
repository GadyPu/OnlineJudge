#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
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
using std::string;
using std::priority_queue;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 256;
typedef unsigned long long ull;
struct Node {
    string name;
    int val, fix, id;
    Node() {}
    Node(string nam, int v, int f, int i) : name(nam), val(v), fix(f), id(i){}
    friend bool operator<(const Node &a, const Node &b) {
        return a.fix == b.fix ? a.id > b.id : a.fix > b.fix;
    }
};
priority_queue<Node> que;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int a, b, k = 1;
    char buf[N], msg[N];
    while (gets(buf)) {
        if (!strcmp(buf, "GET")) {
            if (que.empty()) { puts("EMPTY QUEUE!"); continue; }
            Node ret = que.top(); que.pop();
            printf("%s %d\n", ret.name.c_str(), ret.val);
        } else {
            sscanf(buf + (strchr(buf, ' ') - buf) + 1, "%s %d %d", msg, &a, &b);
            que.push(Node(msg, a, b, k++));
        }
    }
    return 0;
}
