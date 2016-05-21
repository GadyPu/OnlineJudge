#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
struct node{
    char key;
    node *ch[2];
    node(char d) : key(d) { ch[0] = ch[1] = NULL; }
}*root = NULL;
int n = 0;
static int k = -1;
char buf[110];
void built(node *&p){
    k++;
    if (k > n) return;
    if (buf[k] != '#'){
        p = new node(buf[k]);
        built(p->ch[0]);
        built(p->ch[1]);
    }
}
void travle(node *x){
    if (x != NULL){
        travle(x->ch[0]);
        printf("%c ", x->key);
        travle(x->ch[1]);
    }
}
void _free(node *x){
    if (x != NULL){
        _free(x->ch[0]);
        _free(x->ch[1]);
        delete x;
    }
}
int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    while (~scanf("%s", buf)){
        k = -1, root = NULL, n = strlen(buf);
        built(root);
        travle(root);
        _free(root);
        printf("\n");
    }
    return 0;
}
