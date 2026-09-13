/*
Problem 1            
(10 Marks) 
Write a C function to calculate three statistics of an array: minimum value, maximum value, average 
value. Your function should have following signature 
void find_stats(int *arr, int n, int *max, int *min, double 
*avg); 
Where arr is an integer array, n is the number of elements in that array, and after findstats() is 
called, max, min and avg should contain the maximum, minimum, and average value of arr. 
The function must not return anything. You must not use array indexing (arr[i]) in your code. 
Finally, write a main() function to: 
● Take the length n, and elements of arr as input. 
● Declare two integers min, max and one double avg. 
● Call find_stats(arr, n, max, min, avg) 
● Print the values of max, min and avg. 
Input Format 
The first line contains a single integer n. 
The next line contains n space separated integers, elements of arr. 
Output Format 
Print the values of max, min and avg. 
*/

#include<stdio.h>
#include<stdlib.h>

void find_stats(int *arr, int n, int *max, int *min, double *avg);
void find_stats(int *arr, int n, int *max, int *min, double *avg)
{
    *max=*arr;
    *min=*arr;
    int i = 0;
    while(i<n)
    {
        *max = (*(arr + i) > *max)? *(arr + i) : *max ;
        i++;
    }
    i = 0;
    while(i<n)
    {
        *min = (*(arr + i) < *min)? *(arr + i) : *min ;
        i++;
    }
    i = 0;
    int sum = 0;
    while(i<n)
    {
        sum += *(arr +  i);
        i++;
    }
    *avg = sum/n;
    printf("max %d\nmin %d\navg %d", *max, *min, (int) *avg);
}

int main(void)
{
    int *arr, n, max, min;
    double avg;
    scanf("%d",&n);
    arr = malloc(n * sizeof(int));
    if(arr == NULL){ printf("Error!");}
    else
    {
        int i = 0;
        while(i<n)
        {
            scanf("%d", arr + i);
            i++;
        }
        find_stats(arr, n, &max, &min, &avg);
        return 0;
    }
    free(arr);
}

/*
Problem 2            
(10 Marks) 
Write a C function for adding two 2D matrices of the same dimension. Your function should have the 
following signature 
void addmatrix(int **a, int **b, int rows, int cols, int **out); 
The function should take input two 2D arrays a and b, along with their number of rows rows, number 
of columns cols, and output the result of addition of these two matrices into out. This function 
must not return anything. You cannot use array indexing in this function. 
Finally, write a main() function that  
● dynamically allocates memory for a, b, out 
● takes elements of array a and b as input  
● calls pointwisemultiply(a, b, out)  
● prints the modified out from main(). 
Input Format 
The first line of the input contains two integers,  rows and cols.  
The next rows number of lines each contain cols integers, elements of a.  
The next rows number of lines each contain cols integers, elements of b.  
Output Format 
Print the elements of  out.
*/

#include<stdio.h>
#include<stdlib.h>

void addmatrix(int **a, int **b, int rows, int cols, int **out);
void addmatrix(int **a, int **b, int rows, int cols, int **out)
{
    int i = 0;
    while(i<rows)
    {
        int j = 0;
        while(j<cols)
        {
            *(*(out+i)+j) = *(*(a+i)+j) + *(*(b+i)+j) ;
            j++;
        }
        i++;
    }

}

int main(void)
{
    int **a;
    int **b;
    int **out;
    int rows, cols;
    scanf("%d %d",&rows, &cols);
    a = malloc(rows * sizeof(int*));
    b = malloc(rows * sizeof(int*));
    out = malloc(rows * sizeof(int*));
    if(a == NULL || b == NULL || out == NULL){ printf("Error!");}
    int i = 0, j = 0;
    while(i<rows)
    {
        *(a + i) = malloc(cols * sizeof(int));
        *(b + i) = malloc(cols * sizeof(int));
        *(out + i) = malloc(cols * sizeof(int));
        if(a == NULL || b == NULL || out == NULL){ printf("Error!"); return 1;}
        i++;
    }
    i=0;
    while(i< rows)
    {
        j = 0;
        while(j < cols)
        {
            scanf("%d",*(a+i)+j);
            printf(" ");
            j++;
        }
        i++;
    }
    i=0;
    while(i< rows)
    {
        j = 0;
        while(j < cols)
        {
            scanf("%d",*(b+i)+j);
            printf(" ");
            j++;
        }
        i++;
    }
    addmatrix(a, b, rows, cols, out);
    i = 0;
    while(i< rows)
    {
        j = 0;
        while(j < cols)
        {
            printf("%d",*(*(out+i)+j));
            printf(" ");
            j++;
        }
        printf("\n");
        i++;
    }
    i = 0;
    j = 0;
    while(i < rows)
    {
        free(*(a + i));
        free(*(b + i));
        free(*(out + i));
        i++;
    }
    free(a);
    free(b);
    free(out);
    return 0;

}
