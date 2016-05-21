#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<set>
using std::set;
using std::vector;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t, n, v;
    scanf("%d", &t);
    while (t--) {
        set<int> ret;
        vector<int> ans;
        scanf("%d %d", &n, &v);
        ret.insert(v), ans.push_back(v);
        for (int i = 1; i < n; i++) {
            scanf("%d", &v);
            if (!ret.count(v)) ret.insert(v), ans.push_back(v);
        }
        n = ans.size();
        for (int i = 0; i < n; i++) {
            printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
        }
    }
    return 0;
}
