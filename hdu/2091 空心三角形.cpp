#include<cstdio>
void go(char ch, int n) {
    int i, j, k;
    for (i = 1; i < n; i++) {
        for (j = i; j <= n - 1; j++) printf(" ");
        printf("%c", ch);
        for (k = 1; k < (i << 1) - 2 && i > 1; k++) printf(" ");
        if (i > 1) printf("%c", ch);
        printf("\n");
    }
    for (i = 0; i < (n << 1) - 1; i++) printf("%c", ch);
    printf("\n");
}
int main() {
    char ch;
    int n, k = 0;
    while (~scanf("%c", &ch) && ch != '@') {
        if (k) printf("\n");
        k++;
        scanf("%d\n", &n);
        go(ch, n);
    }
    return 0;
}
