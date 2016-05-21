#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<map>
using std::map;
map<int, int> rec;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int num, id, score, rank, targe;
    while (~scanf("%d", &num)) {
        rank = 0, rec.clear();
        while (~scanf("%d %d", &id, &score) && id + score) rec[id] = score;
        targe = rec[num];
        map<int, int>::iterator ite;
        for (ite = rec.begin(); ite != rec.end(); ++ite) {
            if (ite->second > targe) rank++;
        }
        printf("%d\n", rank + 1);
    }
    return 0;
}
