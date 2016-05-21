#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
using std::lower_bound;
using std::upper_bound;
const int Max_N = 1000010;
int arr[Max_N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, v;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &v);
            printf("%d\n", upper_bound(arr, arr + n, v) - lower_bound(arr, arr + n, v));
        }
    }
    return 0;
}
