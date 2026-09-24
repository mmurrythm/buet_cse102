#include<stdio.h>
int main()
{
    long long n;
    scanf("%lld",&n);
    printf("%lld",n);
    if(n==1) return 0;
    do{
        n=(n%2==0)?(n/2):(3*n+1);
        printf(" %lld",n);
    }while(n!=1);
    return 0;
}
