#include<iostream>  
#include<vector>  
#include <cstring>  
#include<algorithm>  
#define rt place[i].val  
const int Max_N = 110;  
typedef char State[82];  
struct node{ State list; int val; }x1, x2;  
std::vector<node> rec[Max_N], place;  
int cmp(const node & a, const node & b){  
    return strcmp(a.list, b.list) == -1 ? 1 : 0;  
}  
bool is_exist(std::vector<node> ve, char *pls){  
    for (int i = 0; i < ve.size(); i++){  
        if (0 == strcmp(pls, ve[i].list)) return true;  
    }  
    return false;  
}  
int main(){  
#ifdef LOCAL  
    freopen("in.txt", "r", stdin);  
    freopen("out.txt", "w+", stdout);  
#endif  
    int t, n, i, k;  
    scanf("%d", &t);  
    while (t--){  
        k = 0;  
        scanf("%d", &n);  
        for (i = 0; i < n; i++){  
            scanf("%s %s %d", x2.list, x1.list, &x2.val);  
            if (0 == place.size() || !is_exist(place, x1.list)){  
                x1.val = k;  
                place.push_back(x1), rec[k++].push_back(x2);  
            } else {  
                int flag = 0, d = 0;  
                for (int j = 0; j < place.size(); j++){  
                    if (0 == strcmp(x1.list, place[j].list)){  
                        d = j;  
                        break;  
                    }  
                }  
                for (int j = 0; j < rec[d].size(); j++){  
                    if (0 == strcmp(x2.list, rec[d][j].list)){  
                        rec[d][j].val += x2.val;  
                        flag = 1;  
                        break;  
                    }  
                }  
                if (!flag) rec[d].push_back(x2);  
            }  
        }  
        std::sort(place.begin(), place.end(), cmp);  
        for (i = 0; i < k; i++){  
            std::sort(rec[rt].begin(), rec[rt].end(), cmp);  
            printf("%s\n", place[i].list);  
            for (int j = 0; j < rec[rt].size(); j++){  
                printf("   |----%s(%d)\n", rec[rt][j].list, rec[rt][j].val);  
            }  
            rec[rt].clear();  
        }  
        place.clear();  
        if (t > 0) printf("\n");  
    }  
    return 0;  
} 
