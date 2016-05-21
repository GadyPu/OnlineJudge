#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
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
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int Max_N = 310;
typedef unsigned long long ull;
struct Node {
    string name;
    int score, id;
    bool operator <(const Node a) const {
        if (a.score != score) return a.score < score;
        return id < a.id;
    }
}A[Max_N], B[Max_N];
int N;
void solve() {
    int f = 0;
    sort(A, A + N);
    rep(i, N) {
        if (A[i].name != B[i].name) {
            if (B[i].score == A[i].score) f = 1;
            else f = -1;
        }
    }
    if (!f) { puts("Right"); return; }
    if (1 == f)  puts("Not Stable");
    else puts("Error");
    rep(i, N) cout << A[i].name << " " << A[i].score << endl;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    std::ios::sync_with_stdio(false);
    while (cin >> N) {
        rep(i, N) { cin >> A[i].name >> A[i].score; A[i].id = i; }
        rep(i, N) cin >> B[i].name >> B[i].score;
        solve();
    }
     return 0;
}
