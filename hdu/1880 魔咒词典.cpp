#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using std::abs;
using std::sort;
using std::pair;
using std::swap;
using std::vector;
using std::multimap;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 100077;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
struct Hash_Set {
    struct edge { char str1[22], str2[82]; int next; }G_1[N], G_2[N];
    int tot_1, tot_2, head_1[N], head_2[N];
    inline void init() {
        tot_1 = 0, cls(head_1, -1);
        tot_2 = 0, cls(head_2, -1);
    }
    inline int hash_func(char *s) {
        int val = 0;
        while (*s != '\0') {
            val = ((val << 1) + (*s - 'a')) % N;
            s++;
        }
        return val;
    }
    inline void insert_1(char *p, char *p1) {
        char *s = p;
        int val = hash_func(p);
        int u = abs(val) % N;
        strcpy(G_1[tot_1].str1, p); strcpy(G_1[tot_1].str2, p1);
        G_1[tot_1].next = head_1[u], head_1[u] = tot_1++;
    }
    inline void insert_2(char *p, char *p1) {
        char *s = p;
        int val = hash_func(p);
        int u = abs(val) % N;
        strcpy(G_2[tot_2].str2, p); strcpy(G_2[tot_2].str1, p1);
        G_2[tot_2].next = head_2[u], head_2[u] = tot_2++;
    }
    inline char *find_1(char *p) {
        char *s = p;
        int val = hash_func(p);
        int u = abs(val) % N;
        for (int i = head_1[u]; ~i; i = G_1[i].next) {
            if (!strcmp(G_1[i].str1, p)) return G_1[i].str2;
        }
        return NULL;
    }
    inline char *find_2(char *p) {
        char *s = p;
        int val = hash_func(p);
        int u = abs(val) % N;
        for (int i = head_2[u]; ~i; i = G_2[i].next) {
            if (!strcmp(G_2[i].str2, p)) return G_2[i].str1;
        }
        return NULL;
    }
}hash;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    char *p;
    int n, k;
    char buf[200], str1[100], str2[100];
    hash.init();
    while (gets(buf)) {
        if (!strcmp(buf, "@END@")) break;
        cls(str2, 0);
        p = strchr(buf, ']');
        k = p - buf;
        strncpy(str1, buf + 1, k - 1), str1[k - 1] = '\0';
        strcpy(str2, p + 2);
        hash.insert_1(str1, str2), hash.insert_2(str2, str1);
    }
    scanf("%d", &n);
    getchar();
    while (n--) {
        gets(buf);
        if (buf[0] == '[') {
            p = strchr(buf, ']');
            k = p - buf;
            strncpy(str1, buf + 1, k - 1), str1[k - 1] = '\0';
            p = hash.find_1(str1);
            puts(!p ? "what?" : p);
        } else {
            p = hash.find_2(buf);
            puts(!p ? "what?" : p);
        }
    }
    return 0;
}
