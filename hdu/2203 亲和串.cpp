#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::sort;
using std::set;
using std::map;
using std::pair;
using std::vector;
using std::multiset;
using std::multimap;
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
char str[Max_N];
struct KMP {
    int i, j, n, m, next[Max_N];
    char text[Max_N << 1], pat[Max_N];
    inline void init() {
        strcpy(text, str);
        strcat(text, str);
    }
    inline void get_next() {
        n = strlen(pat);
        for (i = 1, j = next[0] = 0; i < n; i++) {
            while (j > 0 && pat[i] != pat[j]) j = next[j - 1];
            if (pat[i] == pat[j]) j++;
            next[i] = j;
        }
    }
    inline bool kmp_match() {
        get_next();
        m = strlen(text);
        for (i = j = 0; i < m; i++) {
            while (j > 0 && text[i] != pat[j]) j = next[j - 1];
            if (text[i] == pat[j]) j++;
            if (j == n) return true;
        }
        return false;
    }
}kmp;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%s %s", str, kmp.pat)) {
        kmp.init();
        puts(kmp.kmp_match() ? "yes" : "no");
    }
    return 0;
}
