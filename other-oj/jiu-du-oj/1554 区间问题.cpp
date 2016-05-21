#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using std::sort;
using std::lower_bound;
const int Max_N = 10010;
int arr[Max_N], sum[Max_N], temp[Max_N];
struct Node {
    int v, pos;
    bool operator<(const Node &x) const {
        if (v == x.v) return pos < x.pos;
        return v < x.v;
    }
}rec[Max_N];
void solve(int n, int k) {
    int p = 0;
    for (int i = 0; i < n; i++) {
        p = lower_bound(temp + 1, temp + n, sum[i] + k) - temp;
        if (p == n && sum[n] != k) continue;
        if (rec[p].pos > i && rec[p].v == sum[i] + k) {
            printf("%d %d\n", i + 1, rec[p].pos);
            return;
        } else {
            p++;
            while (rec[p].v == sum[i] + k) {
                if (rec[p].pos > i) {
                    printf("%d %d\n", i + 1, rec[p].pos);
                    return;
                }
                p++;
            }
        }
    }
    puts("No");
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, k;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
            sum[i] = sum[i - 1] + arr[i];
            rec[i].v = sum[i], rec[i].pos = i;
        }
        scanf("%d", &k);
        sort(rec + 1, rec + n);
        for (int i = 1; i <= n; i++) temp[i] = rec[i].v;
        solve(n, k);
    }
    return 0;
}
