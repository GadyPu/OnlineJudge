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
const int M = 7;
const int N = 100001;
const int INF = 0x3f3f3f3f;
struct Matrix {
    typedef vector<int> vec;
    typedef vector<vec> mat;
    inline mat mul(mat &A, mat &B) {
        mat C(sz(A), vec(sz(B[0])));
        rep(i, sz(A)) {
            rep(k, sz(B)) {
                rep(j, sz(B[0])) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
                }
            }
        }
        return C;
    }
    inline mat pow(mat &A, int n) {
        mat ret(sz(A), vec(sz(A[0])));
        rep(i, sz(A)) ret[i][i] = 1;
        while(n) {
            if(n & 1) ret = mul(ret, A);
            A = mul(A, A);
            n >>= 1;
        }
        return ret;
    }
    inline void solve(int a, int b, int n) {
        mat ans(2, vec(2));
        ans[0][0] = a, ans[0][1] = b;
        ans[1][0] = 1, ans[1][1] = 0;
        ans = pow(ans, n - 2);
        printf("%d\n", (ans[0][0] + ans[0][1]) % M);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int a, b, n;
    while(~scanf("%d %d %d", &a, &b, &n), a + b + n) {
        if(1 == n || 2 == n) { puts("1"); continue; }
        go.solve(a, b, n);
    }
    return 0;
}
