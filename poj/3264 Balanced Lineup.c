#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define BASE 2
#define Max_N 50010
#define _max(a,b) ((a)>(b)?(a):(b))
#define _min(a,b) ((a)>(b)?(b):(a))
#define _Log2(_) ((int)(log((double)(_)) / log((double)BASE)))
int _ST[Max_N][20], ST[Max_N][20];
void built(int n){
    int i, j, m;
    int k = _Log2(n);
    for (j = 1; j <= k; j++){
        for (i = 0; i + (1 << j) - 1 < n; i++){
            m = 1 << (j - 1);
            ST[i][j] = _max(ST[i][j - 1], ST[i + m][j - 1]);
            _ST[i][j] = _min(_ST[i][j - 1], _ST[i + m][j - 1]);
        }
    }
}
int query(int x, int y){
    int k = _Log2(y - x + 1);
    int m = (1 << k) - 1;
    return _max(ST[x][k], ST[y - m][k]) - _min(_ST[x][k], _ST[y - m][k]);
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int i, N, Q, x, y;
    while (~scanf("%d %d", &N, &Q)){
        for (i = 0; i < N; i++){
            scanf("%d", &_ST[i][0]);
            ST[i][0] = _ST[i][0];
        }
        built(N);
        for (i = 0; i < Q; i++){
            scanf("%d %d", &x, &y);
            printf("%d\n", query(x - 1, y - 1));
        }
    }
    return 0;
}
