#include<cstdio>
#include<cstdlib>
#include<queue>
#include<functional>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int Max_N = 1510;
ll ans[Max_N];
void init(){
    int arr[4] = { 2, 3, 5 };
    priority_queue<ll, vector<ll>, greater<ll> > que;
    que.push(1);
    for (int i = 1; i <= 1500;){
        ll t = que.top();
        que.pop(), ans[i] = t;
        if (ans[i] == ans[i - 1]){
            continue;
        } else {
            i++;
        }
        for (int j = 0; j < 3; j++) que.push((ll)(t * arr[j]));
    }
}
int main(){
    init();
    int n;
    while (~scanf("%d", &n) && n) printf("%lld\n", ans[n]);
    return 0;
}
