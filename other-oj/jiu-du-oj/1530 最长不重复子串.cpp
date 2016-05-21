#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using std::max;
const int Max_N = 10010;
int vis[26];
char buf[Max_N];
void solve(){
    int i, j, ans = 0, n = strlen(buf);
    for (i = 0; i < n - 1; i++){
        int t = 1;
        memset(vis, 0, sizeof(vis));
        vis[buf[i] - 'a'] = 1;
        for (j = i + 1; j < n; j++){
            if (!vis[buf[j] - 'a']){
                vis[buf[j] - 'a'] = 1;
                t++;
            } else {
                break;
            }
        }
        ans = max(ans, t);
    }
    printf("%d\n", ans);
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%s", buf)) solve();
    return 0;
}
