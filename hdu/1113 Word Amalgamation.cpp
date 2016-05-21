#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<string>
#include<map>
#include<set>
using std::set;
using std::map;
using std::sort;
using std::string;
using std::next_permutation;
set<string> rec;
int _main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int c = 0;
    char buf[10], tmp[10];
    while (~scanf("%s", buf) && c != 2){
        if (!c && strcmp(buf, "XXXXXX") != 0) rec.insert(buf);
        else if (0 == strcmp(buf, "XXXXXX")) c++;
        else {
            int flag = 0, n = strlen(buf);
            strcpy(tmp, buf);
            sort(tmp, tmp + n);
            do{
                if (rec.count(tmp) != 0) flag = 1, printf("%s\n", tmp);
            } while (next_permutation(tmp, tmp + n));
            if (!flag)  printf("NOT A VALID WORD\n", tmp);
            printf("******\n");
        }
    }
    return 0;
}
