#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#define max(a,b) ((a)>(b)?(a):(b))  
int map[5][5],tot,N;  
char buf[6];  
void read()  
{  
    int i,j;  
    getchar();  
    for(i=0;i<N;i++)  
    {  
        gets(buf);  
        for(j=0;j<N;j++)  
        {  
            if(buf[j]=='X')  
                map[i][j]=1;  
            else  
                map[i][j]=0;  
        }  
    }  
}  
int GetPosL(int x,int key)  
{  
    int i;  
    for(i=0;i<N;i++)  
        if(key == map[x][i])  
            return i;  
    return -1;  
}  
int GetPosH(int y,int key)  
{  
    int i;  
    for(i=0;i<N;i++)  
        if(key == map[i][y])  
            return i;  
    return -1;  
}  
int checkoutL(int x)  
{  
    int sign1,sign2;  
    sign1=GetPosL(x,1),sign2=GetPosL(x,2);  
    if(-1 == sign2)  
        return 1;  
    else if((x<sign1 && sign2<sign1) || (x>sign1 && sign2>sign1))  
        return 0;  
    return 1;  
}  
int checkoutH(int y)  
{  
    int sign3,sign4;  
    sign3=GetPosH(y,1),sign4=GetPosH(y,2);  
    if(-1 == sign4)  
        return 1;  
    else if((y<sign3 && sign4<sign3) || (y>sign3 && sign4>sign3))  
        return 0;  
    return 1;  
}  
void PrintRes()  
{  
    int i,j;  
    for(i=0;i<N;i++)  
    {  
        for(j=0;j<N;j++)  
        {  
            if(0 == map[i][j])  
                printf("%c",'.');  
            else if(1 == map[i][j])  
                printf("%c",'X');  
            else  
                printf("%c",'Q');  
        }  
        printf("\n");  
    }  
}  
void dfs(int cur)  
{  
    int i,j;  
    for(i=0;i<N;i++)  
    {  
        for(j=0;j<N;j++)  
        {  
            if(checkoutH(j) && checkoutL(i) && 0 == map[i][j])  
            {  
                map[i][j]=2;  
                dfs(cur+1);  
                map[i][j]=0;  
            }  
        }  
    }  
    tot=max(tot,cur);  
}  
void solve()  
{  
    tot=0;  
    memset(map,0,sizeof(map));  
    read();  
    dfs(0);  
    printf("%d\n",tot);  
}  
int main()  
{  
    while(EOF!=scanf("%d",&N) && 0!=N)  
        solve();  
    return 0;  
}  
