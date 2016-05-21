#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<map>
#include<set>
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
const int Max_N = 100010;
typedef unsigned long long ull;
map<string, int> rec;
void init() {
    rec["zero"] = 0;
    rec["one"] = 1;
    rec["two"] = 2;
    rec["three"] = 3;
    rec["four"] = 4;
    rec["five"] = 5;
    rec["six"] = 6;
    rec["seven"] = 7;
    rec["eight"] = 8;
    rec["nine"] = 9;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    init();
    int a, b, f;
    char str[100], buf[100];
    while (gets(buf)) {
        a = b = f = 0;
        char *p = buf;
        while (true) {
            if (*p == ' ') { p++; continue; }
            sscanf(p, "%s", str);
            if (!strcmp(str, "=")) break;
            if (!f && strcmp(str, "+")) a = a * 10 + rec[str];
            if (!strcmp(str, "+") || f) {
                if (!strcmp(str, "+")) { f = 1, p++; continue; }
                b = b * 10 + rec[str];
            }
            p = p + strlen(str);
        }
        if (!(a + b)) break;
        printf("%d\n", a + b);
    }
    return 0;
}
