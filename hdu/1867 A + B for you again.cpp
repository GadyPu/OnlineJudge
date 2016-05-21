#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::map;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 100010;
typedef unsigned long long ull;
int next[N];
char str1[N], str2[N];
struct KMP {
    int i, j, n, m;
    inline void get_next(char *src) {
        m = strlen(src);
        for (i = 1, j = next[0] = 0; i < m; i++) {
            while (j > 0 && src[i] != src[j]) j = next[j - 1];
            if (src[i] == src[j]) j++;
            next[i] = j;
        }
    }
    inline int kmp_match(char *text, char *pat) {
        n = strlen(text);
        for (i = j = 0; i < n; i++) {
            while (j > 0 && text[i] != pat[j]) j = next[j - 1];
            if (text[i] == pat[j]) j++;
        }
        return j;
    }
}go;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int p, q;
    while (~scanf("%s %s", str1, str2)) {
        go.get_next(str2);
        p = go.kmp_match(str1, str2);
        go.get_next(str1);
        q = go.kmp_match(str2, str1);
        if (p > q || (p == q && -1 == strcmp(str1, str2))) {
            printf("%s%s\n", str1, str2 + p);
        } else {
            printf("%s%s\n", str2, str1 + q);
        }
    }
    return 0;
}
