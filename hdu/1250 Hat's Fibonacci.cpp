#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include<set>
using std::cin;
using std::max;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr,val) memset(arr,val,sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define fork(i, k, n) for (int i = (int)k; i <= (int)n; i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)
struct BigN {
    typedef unsigned long long ull;
    static const int Max_N = 2010;
    int len, data[Max_N];
    BigN() { memset(data, 0, sizeof(data)), len = 0; }
    BigN(const int num) {
        memset(data, 0, sizeof(data));
        *this = num;
    }
    BigN(const char *num) {
        memset(data, 0, sizeof(data));
        *this = num;
    }
    void clear() { len = 0, memset(data, 0, sizeof(data)); }
    BigN& clean(){ while (len > 1 && !data[len - 1]) len--;  return *this; }
    string str() const {
        string res = "";
        for (int i = len - 1; ~i; i--) res += (char)(data[i] + '0');
        if (res == "") res = "0";
        res.reserve();
        return res;
    }
    BigN operator = (const int num) {
        int j = 0, i = num;
        do data[j++] = i % 10; while (i /= 10);
        len = j;
        return *this;
    }
    BigN operator = (const char *num) {
        len = strlen(num);
        for (int i = 0; i < len; i++) data[i] = num[len - i - 1] - '0';
        return *this;
    }
    BigN operator + (const BigN &x) const {
        BigN res;
        int n = max(len, x.len) + 1;
        for (int i = 0, g = 0; i < n; i++) {
            int c = data[i] + x.data[i] + g;
            res.data[res.len++] = c % 10;
            g = c / 10;
        }
        return res.clean();
    }
    BigN operator * (const BigN &x) const {
        BigN res;
        int n = x.len;
        res.len = n + len;
        for (int i = 0; i < len; i++) {
            for (int j = 0, g = 0; j < n; j++) {
                res.data[i + j] += data[i] * x.data[j];
            }
        }
        for (int i = 0; i < res.len - 1; i++) {
            res.data[i + 1] += res.data[i] / 10;
            res.data[i] %= 10;
        }
        return res.clean();
    }
    BigN operator * (const int num) const {
        BigN res;
        res.len = len + 1;
        for (int i = 0, g = 0; i < len; i++) res.data[i] *= num;
        for (int i = 0; i < res.len - 1; i++) {
            res.data[i + 1] += res.data[i] / 10;
            res.data[i] %= 10;
        }
        return res.clean();
    }
    BigN operator - (const BigN &x) const {
        assert(x <= *this);
        BigN res;
        for (int i = 0, g = 0; i < len; i++) {
            int c = data[i] - g;
            if (i < x.len) c -= x.data[i];
            if (c >= 0) g = 0;
            else g = 1, c += 10;
            res.data[res.len++] = c;
        }
        return res.clean();
    }
    BigN operator / (const BigN &x) const {
        BigN res, f = 0;
        for (int i = len - 1; ~i; i--) {
            f *= 10;
            f.data[0] = data[i];
            while (f >= x) {
                f -= x;
                res.data[i]++;
            }
        }
        res.len = len;
        return res.clean();
    }
    BigN operator % (const BigN &x) {
        BigN res = *this / x;
        res = *this - res * x;
        return res;
    }
    BigN operator += (const BigN &x) { return *this = *this + x; }
    BigN operator *= (const BigN &x) { return *this = *this * x; }
    BigN operator -= (const BigN &x) { return *this = *this - x; }
    BigN operator /= (const BigN &x) { return *this = *this / x; }
    BigN operator %= (const BigN &x) { return *this = *this % x; }
    bool operator <  (const BigN &x) const {
        if (len != x.len) return len < x.len;
        for (int i = len - 1; ~i; i--) {
            if (data[i] != x.data[i]) return data[i] < x.data[i];
        }
        return false;
    }
    bool operator >(const BigN &x) const { return x < *this; }
    bool operator<=(const BigN &x) const { return !(x < *this); }
    bool operator>=(const BigN &x) const { return !(*this < x); }
    bool operator!=(const BigN &x) const { return x < *this || *this < x; }
    bool operator==(const BigN &x) const { return !(x < *this) && !(x > *this); }
    friend istream& operator >> (istream &in, BigN &x) {
        string src;
        in >> src;
        x = src.c_str();
        return in;
    }
    friend ostream& operator << (ostream &out, const BigN &x) {
        out << x.str();
        return out;
    }
}A[5];
void solve(int n) {
    fork(i, 1, 4) A[i] = 1;
    if (n < 5) cout << A[n] << endl;
    else {
        int x = 1;
        fork(i, 5, n) {
            A[0] = A[1] + A[2] + A[3] + A[4];
            A[x] = A[0];
            if (++x == 5) x = 1;
        }
        cout << A[0] << endl;
    }
    rep(i, 5) A[i].clear();
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    std::ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        solve(n);
    }
    return 0;
}
