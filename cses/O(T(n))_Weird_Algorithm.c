#include<stdio.h>
void next(long long n) //recursive
{
    printf("%lld ",n);
    if(n==1) return;
    if (n % 2 == 0)
    {
      next(n / 2);
    }
    else
    {
        next(3 * n + 1);
    }
}
int main()
{
  long long n;
  scanf("%lld",&n);
  next(n);
  return 0;
}
