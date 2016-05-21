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
const int M = 1000;
const int N = 100001;
const int INF = 0x3f3f3f3f;
void pow_mod(int A, int B) {
    int ans = 1;
    while(B) {
        if(B & 1) ans = ans * A % M;
        A = A * A % M;
        B >>= 1;
    }
    printf("%d\n", ans);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int A, B;
    while(~scanf("%d %d", &A, &B), A + B) {
        pow_mod(A, B);
    }
    return 0;
}
