#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<stack>
#include<set>
using std::cin;
using std::sort;
using std::pair;
using std::stack;
using std::string;
using std::getline;
#define pb(e) push_back(e)
#define sz(c) (int)(c).size()
#define mp(a, b) make_pair(a, b)
#define all(c) (c).begin(), (c).end()
#define iter(c) decltype((c).begin())
#define cls(arr, val) memset(arr, val, sizeof(arr))
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define tr(c, i) for(iter(c) i = (c).begin(); i != (c).end(); ++i)
const int N = 5010;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
class ExpCalc {
private:
    string ret;
    stack<char> op;
    stack<double> num;
    inline void erase() {
        ret = "";
        while (!op.empty()) op.pop();
        while (!num.empty()) num.pop();
    }
    inline bool is_digit(char ch) {
        return ch >= '0' && ch <= '9';
    }
    inline bool get_op(char ch) {
        char buf[10] = "+-*/";
        for (int i = 0; i < 4; i++) {
            if (buf[i] == ch) return true;
        }
        return false;
    }
    inline int cmp(char ch) {
        switch (ch) {
            case '+':
            case '-': return 1;
            case '*':
            case '/': return 2;
        }
        return 0;
    }
    inline double calc(double d1, double d2, char ch) {
        double val = 0.0;
        switch (ch) {
            case '+': val = d1 + d2;
                break;
            case '-': val = d2 - d1;
                break;
            case '*': val = d1 * d2;
                break;
            case '/': val = d2 / d1;
                break;
        }
        return val;
    }      
public:
    ExpCalc() { erase(); }
    ~ExpCalc() { erase(); }
    inline void InfixToPostfix(const string src) {
        int n = src.length();
        for (int i = 0; i < n;) {
            if (' ' == src[i] || '=' == src[i]) { i++; continue; }
            if ('(' == src[i]) op.push(src[i++]);
            if (')' == src[i]) {
                while (op.top() != '(') {
                    ret += op.top(); ret += ' ';
                    op.pop();
                }
                op.pop(); i++;
            } else if (get_op(src[i])) {
                while (!op.empty() && cmp(op.top()) >= cmp(src[i])) {
                    ret += op.top(); ret += ' ';
                    op.pop();
                }
                op.push(src[i++]);
            } else {
                while (is_digit(src[i]) || '.' == src[i]) {
                    ret += src[i++];
                }
                ret += ' ';
            }
        }
        while (!op.empty()) {
            ret += op.top(); ret += ' ';
            op.pop();
        }
        ret += '=';
    }
    inline double PostfixCalc() {
        int n = ret.length();
        for (int i = 0; i < n;) {
            if (' ' == ret[i] || '=' == ret[i]) { i++; continue; }
            if (get_op(ret[i])) {
                double d1 = num.top(); num.pop();
                double d2 = num.top(); num.pop();
                num.push(calc(d1, d2, ret[i++]));
            } else if (is_digit(ret[i]) || '.' == ret[i]) {
                double x = 0.0;
                while (is_digit(ret[i])) {
                    x = x * 10 + ret[i++] - '0';
                }
                if ('.' == ret[i]) {
                    i++;
                    double y = 0.0, k = 10.0;
                    while (is_digit(ret[i])) {
                        y += (ret[i++] - '0') / k;
                        k *= 10;
                    }
                    x += y;
                }
                num.push(x);
            }
        }
        return num.top();
    }
};
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    string src;
    while (getline(cin, src) && src != "0") {
        ExpCalc work;
        work.InfixToPostfix(src);
        printf("%.2lf\n", work.PostfixCalc());
    }
    return 0;
}
