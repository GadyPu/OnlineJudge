#include<algorithm>
#include<cstdio>
#include<map>
using std::map;
map<int,int> rec;
int main() {
    int n, v, res, cnt;
    while (~scanf("%d", &n)) {
        res = cnt = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v);
            rec[v]++;
            if (rec[v] > cnt) cnt = rec[v], res = v;
        }
        printf("%d\n", res);
        rec.clear();
    }
    return 0;
}
