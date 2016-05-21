#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using std::set;
using std::sort;
using std::pair;
using std::swap;
using std::queue;
using std::multiset;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 110;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
struct Node {
    int age;
    char name[N];
    inline bool operator<(const Node &x) const {
        return age > x.age;
    }
}A[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n;
    char buf[200], digit[5];
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        getchar();
        rep(i, n) {
            gets(buf);
            int v, j = 0, len = strlen(buf);
            for (; j < 4; j++) digit[j] = buf[len - 4 + j];
            digit[j] = '\0'; v = atoi(digit);
            buf[len - 5] = '\0';
            A[i].age = v, strcpy(A[i].name, buf);
        }
        sort(A, A + n);
        rep(i, n) printf("%s\n", A[i].name);
    }
    return 0;
}
