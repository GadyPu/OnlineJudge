#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
typedef unsigned long long ull;
const int Max_N = 100010;
ull res;
int arr[Max_N], temp[Max_N];
void Merge(int *A, int l, int m, int r) {
    int p = 0;
    int x = l, y = m + 1;
    while (x <= m && y <= r) {
        if (A[x] > A[y]) res += m - x + 1, temp[p++] = A[y++];
        else temp[p++] = A[x++];
    }
    while (x <= m) temp[p++] = A[x++];
    while (y <= r) temp[p++] = A[y++];
    for (x = 0; x < p; x++) A[l + x] = temp[x];
}
void MergeSort(int *A, int l, int r) {
    int mid;
    if (l < r) {
        mid = (l + r) >> 1;
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
        res = 0;
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        MergeSort(arr, 0, n - 1);
        printf("%lld\n", res);
    }
    return 0;
}
