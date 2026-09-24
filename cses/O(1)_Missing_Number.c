#include<stdio.h>
int main()
{
    long long n, j, miss=0;
    scanf("%lld",&n);
    for(int i =1;i<n;i++)
    {
        scanf("%lld",&j);
        miss+=j;
    }
    miss= (n*(n+1)/2) - miss;
    printf("%lld",miss);
    return 0;
}
