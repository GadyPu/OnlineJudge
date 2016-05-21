#include<functional>
#include<algorithm>
#include<iostream>
#include<string>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
using std::vector;
using std::greater;
using std::priority_queue;
priority_queue<int> que1;
priority_queue<int, vector<int>, greater<int> >que2;
void solve(){
    int v;
    char buf[10];
    scanf("%s %d", buf, &v);
    if ('u' == buf[1]){
        que2.push(v);
    } else {
        while(!que2.empty()){
            int x = que2.top();
            if (x <= v) que1.push(x), que2.pop();
            else break;
        }
        if (que1.empty()) puts("No Element!");
        else printf("%d\n", que1.top()), que1.pop();
    }
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n)){
        while (n--) solve();
        while (!que1.empty()) que1.pop();
        while (!que2.empty()) que2.pop();
        printf("\n");
    }
    return 0;
}
