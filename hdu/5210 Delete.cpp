#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
using std::sort;
const int Max_N = 1010;
int arr[Max_N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, k, tot, ret, cnt;
    while (~scanf("%d", &n)) {
        tot = 0;
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        scanf("%d", &k);
        sort(arr, arr + n);
        for (int i = 0; i < n;) {
            ret = arr[i], cnt = 0;
            for (; ret == arr[i]; i++) cnt++;
            tot++;
        }
        if (n - tot <= k) printf("%d\n", n - k);
        else printf("%d\n", tot);
    }
    return 0;
}
