#include<stdio.h>
#include<string.h>
void capitalizeWords(char str[]);
void capitalizeWords(char str[])
{
    int i = 0;
    while(str[i]!= '\0')
    {
        if(i == 0 || str[i-1]==' ')
        {
            if( str[i]>= 'a' && str[i]<= 'z')  // < less than, > greater than
            {
                str[i] = str[i] - 'a' + 'A';
            }
        }
        i++;
    }
    str[i]='\0';
    puts(str);
}

char mostFrequentChar(char str[]);
/*char mostFrequentChar(char str[])
{
    int tracker[26][2] = {0};
    int unique_count = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            int found = 0;

            for (int j = 0; j < unique_count; j++)
            {
                if (tracker[j][0] == str[i])
                {
                    tracker[j][1]++;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                tracker[unique_count][0] = str[i];
                tracker[unique_count][1] = 1;
                unique_count++;
            }
        }
        i++;
    }

    int max_idx = 0;
    for (int k = 1; k < unique_count; k++)
    {
        if (tracker[k][1] > tracker[max_idx][1])
        {
            max_idx = k;
        }
    }

    char result = (char)tracker[max_idx][0];
    printf("%c\n", result);
    return result;
}
*/

char mostFrequentChar(char str[])
{
    int tracker[26][2] = {0};
    int unique_count = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            int found = 0;
            for (int j = 0; j < unique_count; j++)
            {
                if (tracker[j][0] == str[i])
                {
                    tracker[j][1]++;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                tracker[unique_count][0] = str[i];
                tracker[unique_count][1] = 1;
                unique_count++;
            }
        }
        i++;
    }
    int max_idx = 0;
    for (int k = 1; k < unique_count; k++)
    {
        if (tracker[k][1] > tracker[max_idx][1])
        {
            max_idx = k;
        }
    }

    char result = (char)tracker[max_idx][0];
    printf("%c\n", result);
    return result;
}

int main()
{
    char str1[100];
    char str2[100];
    scanf("%[^\n]", str1);
    strcpy(str2, str1); //would manually copied string but i'm lazy
    capitalizeWords(str1);
    mostFrequentChar(str2);
    return 0;
}
