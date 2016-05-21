#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
using std::map;
using std::fabs;
using std::pair;
using std::swap;
using std::string;
using std::next_permutation;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 20;
const double eps = 1E-7;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
int arr[4];
char ret[4][10];
map<string, int> A;
bool dfs(int n) {
    if (1 == n) {
        return arr[0] == 24;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int a = arr[i], b = arr[j];
            arr[j] = arr[n - 1];
            arr[i] = a + b;
            if (dfs(n - 1)) return true;
            arr[i] = a - b;
            if (dfs(n - 1)) return true;
            arr[i] = b - a;
            if (dfs(n - 1)) return true;
            arr[i] = a * b;
            if (dfs(n - 1)) return true;
            if (b != 0 && 0 == a % b) {
                arr[i] = a / b;
                if (dfs(n - 1)) return true;
            }
            if (a != 0 && 0 == b % a) {
                arr[i] = b / a;
                if (dfs(n - 1)) return true;
            }
            arr[i] = a;
            arr[j] = b;
        }
    }
    return false;
}
void init() {
    A["A"] = 1;
    A["2"] = 2;
    A["3"] = 3;
    A["4"] = 4;
    A["5"] = 5;
    A["6"] = 6;
    A["7"] = 7;
    A["8"] = 8;
    A["9"] = 9;
    A["10"] = 10;
    A["J"] = 11;
    A["Q"] = 12;
    A["K"] = 13;
}
bool solve() {
    for (int i = 0; i < 4; i++) {
        arr[i] = A[ret[i]];
    }
    do {
        if (dfs(4)) return true;
    } while (next_permutation(arr, arr + 4));
    return false;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    init();
    while (~scanf("%s %s %s %s", ret[0], ret[1], ret[2], ret[3])) {
        puts(solve() ? "Yes" : "No");
    }
    return 0;
}
