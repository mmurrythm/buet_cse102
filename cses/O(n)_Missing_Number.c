#include<stdio.h>
int main()
{
    long long n, miss;
    scanf("%lld",&n);
    for(int i =1;i<n;i++) //O(n)
    {
        scanf("%lld",&j);
        miss+=j;
    }
    miss= (n*(n+1)/2) - miss; //O(1)
    printf("%lld",miss);
    return 0;
}
