#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using std::max;
const int Max_N = 200010;
char ret[Max_N];
void solve() {
    int i, j, ans = 0, n = strlen(ret);
    for (i = 0; i < n; i++) {
        for (j = 0; i >= j && i + j < n; j++) {
            if (ret[i - j] != ret[i + j]) break;
            ans = max(ans, j << 1 | 1);
        }
        for (j = 0; i >= j && i + j + 1 < n; j++) {
            if (ret[i - j] != ret[i + j + 1]) break;
            ans = max(ans, (j << 1) + 2);
        }
    }
    printf("%d\n", ans);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (gets(ret)) solve();
    return 0;
}
