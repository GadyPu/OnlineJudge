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
const int M = 9973;
typedef unsigned long long ull;
struct Matrix {
    typedef vector<ull> vec;
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
        mat B(sz(A), vec(sz(A[0])));
        rep(i, sz(A)) B[i][i] = 1;
        while(n) {
            if(n & 1) B = mul(B, A);
            A = mul(A, A);
            n >>= 1;
        }
        return B;
    }
    inline void solve(int n, int k) {
        ull v, ans = 0;
        mat ret(n, vec(n));
        rep(i, n) {
            rep(j, n) {
                scanf("%lld", &v);
                v %= M;
                ret[i][j] = v;
            }
        }
        ret = pow(ret, k);
        rep(i, n) {
            ans += ret[i][i];
            ans %= M;
        }
        printf("%lld\n", ans);
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        go.solve(n, k);
    }
    return 0;
}
