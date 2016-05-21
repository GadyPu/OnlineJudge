#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<iostream>
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    double a, b;
    scanf("%d", &n);
    std::priority_queue<double> ans;
    while (n--){
        scanf("%lf", &a);
        ans.push(a);
    }
    while (ans.size() > 1){
        a = ans.top(), ans.pop();
        b = ans.top(), ans.pop();
        ans.push(2 * sqrt(a * b));
    }
    printf("%.3lf", ans.top());
    return 0;
}
