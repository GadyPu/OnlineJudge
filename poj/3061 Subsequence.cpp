#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using std::min;
using std::lower_bound;
const int Max_N = 100010;
int arr[Max_N], sum[Max_N];
void solve(int n, int s) {
    int res = n;
    if (s > sum[n] || s < sum[1]) { puts("0"); return; }
    for (int i = 0; sum[i] + s <= sum[n]; i++) {
        int t = lower_bound(sum + i, sum + n, sum[i] + s) - sum;
        res = min(res, t - i);
    }
    printf("%d\n", res);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, s;
    while (~scanf("%d", &t)) {
        while (t--) {
            scanf("%d %d", &n, &s);
            for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
                sum[i + 1] = sum[i] + arr[i];
            }
            solve(n, s);
        }
    }
    return 0;
}
