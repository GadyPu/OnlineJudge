#include<functional>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
using std::vector;
using std::greater;
using std::priority_queue;
typedef unsigned long long ull;
const int Max_N = 5843;
ull ans[Max_N];
void init() {
    int arr[5] = { 2, 3, 5, 7 };
    priority_queue<ull, vector<ull>, greater<ull> > que;
    que.push(1);
    for (int i = 1; i <= Max_N;) {
        ull t = que.top();
        que.pop(), ans[i] = t;
        if (ans[i] == ans[i - 1]) {
            continue;
        } else {
            i++;
        }
        for (int j = 0; j < 4; j++) que.push((ull)(t * arr[j]));
    }
}
int main() {
    init();
    int n;
    while (~scanf("%d", &n) && n) {
        if (n % 10 == 1 && n % 100 != 11) 
            printf("The %dst humble number is %lld.\n", n, ans[n]);
        else if (n % 10 == 2 && n % 100 != 12) 
            printf("The %dnd humble number is %lld.\n", n, ans[n]);
        else if (n % 10 == 3 && n % 100 != 13) 
            printf("The %drd humble number is %lld.\n", n, ans[n]);
        else printf("The %dth humble number is %lld.\n", n, ans[n]);
    }
    return 0;
}
