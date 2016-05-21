#include<algorithm>
#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    std::ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        string s1, s2, buf;
        cin >> buf;
        for (int i = 0; buf[i]; i++) {
            if (i & 1) s2 = buf[i] + s2;
            else s1 += buf[i];
        }
        cout << s1 << endl << s2 << endl;
    }
    return 0;
}
