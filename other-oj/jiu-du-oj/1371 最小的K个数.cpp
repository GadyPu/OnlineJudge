#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
using std::sort;
const int Max_N = 200010;
int arr[Max_N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, k;
    while (~scanf("%d %d", &n, &k)) {
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        sort(arr, arr + n);
        for (int i = 0; i < k; i++) {
            printf("%d%c", arr[i], i < k - 1 ? ' ' : '\n');
        }
    }
    return 0;
}
