#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
using std::string;
using std::vector;
using std::cin;
const int Max_N = 100010;
char buf[Max_N], temp[Max_N];
void reverse(char *src, int n){
    int i, j = n - 1;
    for (i = 0; i < j; i++, j--){
        char tp = src[i];
        src[i] = src[j];
        src[j] = tp;
    }
}
void solve(int n){
    int i, j;
    vector<string> ans;
    for (i = 0; i < n; i++){
        if (buf[i] != ' ' || !i){
            j = 0;
            for (; buf[i] != ' ' && i < n; i++) temp[j++] = buf[i];
            temp[j] = '\0';
            reverse(temp, j);
            ans.push_back(temp);
        }
    }
    if (buf[n - 1] == ' ') ans.push_back("");
    int t = ans.size();
    for (i = 0; i < t; i++){
        printf("%s%c", ans[i].c_str(), i < t - 1 ? ' ' : '\n');
    }
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n;
    while (~scanf("%d", &n) && n){
        while (getchar() != '\n');
        gets(buf);
        solve(n); 
    }
    return 0;
}
