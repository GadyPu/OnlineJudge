#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using std::sort;
using std::lower_bound;
const int Max_N = 100010;
struct node {
    int v, id;
}rec[Max_N];
int arr[Max_N];
bool cmp(node &a, node &b) {
    if (a.v == b.v) return a.id < b.id;
    return a.v < b.v;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, a, b, pos;
    while (~scanf("%d %d", &n, &m)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &rec[i].v);
            rec[i].id = i + 1;
        }
        sort(rec, rec + n, cmp);
        for (int i = 0; i < n; i++) arr[i] = rec[i].v;
        while (m--) {
            scanf("%d %d", &a, &b);
            pos = lower_bound(arr, arr + n, b) - arr;
            node &k = rec[pos + a - 1];
            if (k.v == b) printf("%d\n", k.id);
            else puts("0");
        }
    }
    return 0;
}
