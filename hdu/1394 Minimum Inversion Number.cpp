#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#define mid ((l+r)>>1)
using std::min;
const int Max_N = 5010;
const int INF = ~0u >> 1;
int cnt, arr[Max_N], ret[Max_N], temp[Max_N];
void Merge(int *A, int l, int m, int r) {
    int p = 0;
    int x = l, y = m + 1;
    while (x <= m && y <= r) {
        if (A[x] > A[y]) cnt += m - x + 1, temp[p++] = A[y++];
        else temp[p++] = A[x++];
    }
    while (x <= m) temp[p++] = A[x++];
    while (y <= r) temp[p++] = A[y++];
    for (x = 0; x < p; x++) A[l + x] = temp[x];
}
void MergeSort(int *A, int l, int r) {
    if (l < r) {
        MergeSort(A, l, mid);
        MergeSort(A, mid + 1, r);
        Merge(A, l, mid, r);
    }
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]), ret[i] = arr[i];
        cnt = 0;
        MergeSort(arr, 0, n - 1);
        int res = INF;
        for (int i = 0; i < n; i++) {
            cnt = cnt + n - ret[i] - ret[i] - 1;
            res = min(res, cnt);
        }
        printf("%d\n", res);
    }
    return 0;
}
