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
const int N = 61;
typedef char Word[61];
Word str1, str2, st[11];
void solve(int n) {
    bool f;
    int i, j, k, len = 0;
    for (i = 0; i < N - 3; i++) {
        for (j = 3; j < N - i; j++) {
            strncpy(str1, st[0] + i, j); str1[j] = '\0';
            f = true;
            for (k = 1; k < n; k++) {
                if (!strstr(st[k], str1)) { f = false; break; }
            }
            if (f && j > len) {
                len = j;
                strcpy(str2, str1);
            }
            if (f && j == len) {
                if (strcmp(str1, str2) < 0) strcpy(str2, str1);
            }
        }
    }
    puts(!len ? "no significant commonalities" : str2);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        rep(i, n) scanf("%s", st[i]);
        solve(n);
    }
    return 0;
}
