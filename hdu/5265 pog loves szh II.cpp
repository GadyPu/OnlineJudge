#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<set>
using std::max;
using std::multiset;
const int Max_N = 100010;
typedef unsigned long long ull;
ull n, p, arr[Max_N];
void solve() {
    ull res = 0;
    multiset<ull> rec;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
        rec.insert(arr[i] %= p);
    }
    multiset<ull>::iterator ite;
    for (int i = 0; i < n; i++) {
        rec.erase(rec.find(arr[i]));
        ite = rec.lower_bound(p - arr[i]);
        ull v1 = *--ite;
        ite = rec.lower_bound(2 * p - arr[i]);
        ull v2 = *--ite;
        res = max(res, max((v1 + arr[i]) % p, (v2 + arr[i]) % p));
        rec.insert(arr[i]);
    }
    printf("%lld\n", res);
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%lld %lld", &n, &p)) solve();
    return 0;
}
