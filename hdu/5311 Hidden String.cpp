#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::map;
using std::endl;
using std::find;
using std::pair;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 100001;
const char* tar = "anniversary";
char src[110];
bool solve() {
    char s1[20], s2[20], s3[20];
    for(int i = 0; i < 10 ;i++) {
        for(int j = i + 1; j < 10; j++) {
            cls(s1, 0), cls(s2, 0), cls(s3, 0);
            strncpy(s1, tar, i + 1);
            strncpy(s2, tar + i + 1, j - i);
            strncpy(s3, tar + j + 1, 11 - j);
            char *p1 = strstr(src, s1);
            if(!p1) continue;
            char *p2 = strstr(p1 + strlen(s1), s2);
            if(!p2) continue;
            char *p3 = strstr(p2 + strlen(s2), s3);
            if(!p3) continue;
            if(p1 && p2 && p3) return true;
        }
    }
    return false;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", src);
        puts(solve() ? "YES" : "NO");
    }
    return 0;
}
