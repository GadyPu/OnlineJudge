#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
const int Max_N = 100010;
int arr[Max_N];
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int i, ret, k, n;
    while (~scanf("%d", &n)){
        int f = 0;
        for (i = 0; i < n; i++) scanf("%d", &arr[i]);
        std::sort(arr, arr + n);
        for (i = 0; i < n;){
            k = 0, ret = arr[i];
            for (; ret == arr[i]; i++) k++;
            if (k > n >> 1){
                f = 1;
                printf("%d\n", ret);
                break;
            }
        }
        if (!f) printf("-1\n");
    }
    return 0;
}
