#include<stdio.h>
#include<stdlib.h>
int** clone_matrix (int **m, int rows , int cols );
int main(void)
{
    int** m;
    int** new_m;
    int rows,cols;
    scanf("%d %d",&rows ,&cols);
    m = malloc(rows * sizeof(int*));
    for(int i = 0; i<rows; i++)
    {
        *(m + i) = malloc(cols * sizeof(int));
        for(int j = 0; j<cols;j++)
        {
            scanf("%d",*(m+i) + j);
        }
    }
    new_m = clone_matrix(m, rows,cols);
    printf("m address: %p\nnew_m address: %p",(void*) m,(void*) new_m); //new address is chosen randomly each time, so don't get afraid if it doesn't match.
    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j<cols;j++)
        {
            printf("%d ",*(*(new_m+i) + j));
        }
        printf("\n");
    }
    for(int i = 0;i<rows;i++)
    {
        free(*(m+i));
    }
    free(m);
    for(int i = 0;i<rows;i++)
    {
        free(*(new_m+i));
    }
    free(new_m);
    return 0;
}
int** clone_matrix (int **m, int rows , int cols )
{
    int** new_m = malloc(rows * sizeof(int*));
    for(int i = 0; i<rows; i++)
    {
        *(new_m + i) = malloc(cols * sizeof(int));
    }
    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j < cols;j++)
        {
            *(*(new_m+i)+j) = *(*(m+i)+j);
        }
    }
    return new_m;
}
