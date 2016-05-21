#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<set>
#include<map>
using std::map;
map<int, int> rec;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, v, k;
    while (~scanf("%d %d", &n, &k)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &v);
            rec[v]++;
        }
        while (k--) {
            scanf("%d", &v);
            map<int, int>::iterator ite = rec.lower_bound(v);
            if (ite == rec.end() || ite->first > v) puts("0");
            else printf("%d\n", ite->second), rec.erase(v);
        }
    }
    return 0;
}
