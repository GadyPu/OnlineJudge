#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<memory.h>  
#define Max_Szie 5000 + 2  
int A[Max_Szie], B[Max_Szie], C[Max_Szie];  
void solve(int n)  
{  
    memset(A, 0, sizeof(A));  
    memset(B, 0, sizeof(B));  
    memset(C, 0, sizeof(C));  
    A[0] = 1, B[0] = 1;  
    int i, j;  
    for (i = 2; i < n; i++)  
    {  
        int c = 0;  
        for (j = 0; j < Max_Szie; j++)  
        {  
            int temp = A[j] + B[j] + c;  
            c = temp / 10;  
            C[j] = temp % 10 ;  
        }  
        memcpy(A, B, sizeof(B));  
        memcpy(B, C, sizeof(C));  
    }  
    j = Max_Szie - 1;  
    while (!C[j])  
        j--;  
    for (; j >= 0; j--)  
        printf("%d", C[j]);  
    printf("\n");  
}  
int main()  
{  
    int n;  
    while (EOF != scanf("%d", &n))  
        solve(n);  
    return 0;  
}  
