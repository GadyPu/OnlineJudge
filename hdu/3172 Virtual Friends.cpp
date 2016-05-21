#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<map>
using std::map;
using std::string;
const int Max_N = 100010;
struct UnionFind {
    map<string, int> rec;
    int num[Max_N], par[Max_N];
    void init() {
        for (int i = 1; i < Max_N; i++) {
            par[i] = i;
            num[i] = 1;
        }
        rec.clear();
    }
    inline int find(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    inline void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x != y){
            par[x] = y;
            num[y] += num[x];
            printf("%d\n", num[y]);
        } else {
            printf("%d\n", num[y]);
        }
    }
    inline void gogo() {
        int n, cnt = 1;
        char s1[100], s2[100];
        scanf("%d", &n);
        while (n--) {
            scanf("%s %s", s1, s2);
            if (!rec[s1]) rec[s1] = cnt++;
            if (!rec[s2]) rec[s2] = cnt++;
            unite(rec[s1], rec[s2]);
        }
    }
}ans;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    while (~scanf("%d", &t)) {
        while (t--) ans.init(), ans.gogo();
    }
    return 0;
}
