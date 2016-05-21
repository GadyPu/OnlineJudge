#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<map>
using std::map;
using std::string;
map<string, int> rec;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    char buf[20];
    while (~scanf("%d", &n) && n) {
        int tot = 0;
        for (int i = 0; i < n; i++) scanf("%s", buf), rec[buf]++;
        map<string, int>::iterator ite;
        for (ite = rec.begin(); ite != rec.end(); ++ite) {
            if (ite->second > tot) {
                tot = ite->second;
                strcpy(buf, ite->first.c_str());
            }
        }
        printf("%s\n", buf);
        rec.clear();
    }
    return 0;
}
