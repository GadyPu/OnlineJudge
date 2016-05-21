#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
using std::max;
const int shift = 500000;
const int Max_N = 1000100;
bool vis[Max_N];
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, v;
    while (~scanf("%d %d", &n, &m)){
        int mx = 0, cnt = 0;
        memset(vis, false, sizeof(vis));
        for (int i = 0; i < n; i++){
            scanf("%d", &v);
            vis[v + shift] = true;
            mx = max(mx, v + shift);
        }
        for (int i = mx; i > -1; i--){
            if (vis[i]){
                cnt++;
                printf("%d%c", i - shift, cnt < m ? ' ' : '\n');
            }
            if (cnt == m) break;
        }
    }
    return 0;
}
