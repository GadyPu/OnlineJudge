#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<set>
using std::multiset;
using std::lower_bound;
struct Node {
    int val, pos;
    Node(int _val = 0, int _pos = 0) :val(_val), pos(_pos){}
};
struct cmp{
    bool operator()(const Node &a, const Node &b) const {
        if (a.val == b.val) return a.pos < b.pos;
        return a.val < b.val;
    }
};
multiset<Node,cmp> rec;
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w+", stdout);
#endif
    int n, m, v;
    while (~scanf("%d %d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &v);
            Node t(v, i);
            rec.insert(t);
        }
        while (m--) {
            scanf("%d", &v);
            multiset<Node, cmp>::iterator ite = rec.lower_bound(v);
            if (ite == rec.end() || v < ite->val) puts("-1");
            else printf("%d\n", ite->pos), rec.erase(ite);
        }
        rec.clear();
    }
    return 0;
}
