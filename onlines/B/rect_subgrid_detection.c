#include<stdio.h>
#include<stdlib.h>
void find_active_bounding_box (int **m, int rows , int cols , int *r1 , int *c1 , int *r2 , int *c2);
int main(void)
{
    int** m;
    int rows, cols;
    int* r1;
    int* c1;
    int* r2;
    int* c2;
    scanf("%d %d",&rows, &cols);
    m = malloc(rows * sizeof(int*));
    r1 = malloc(sizeof(int));
    c1 = malloc(sizeof(int));
    r2 = malloc(sizeof(int));
    c2 = malloc(sizeof(int));
    for(int i = 0; i<rows; i++)
    {
        *(m + i) = malloc(cols * sizeof(int));
        for(int j = 0; j<cols;j++)
        {
            scanf("%d",*(m+i) + j);
        }
    }
    find_active_bounding_box(m,rows,cols,r1,c1,r2,c2);
    printf("*r1 = %d\n*c1 = %d\n*r2 = %d\n*c2 = %d",*r1,*c1,*r2,*c2);
    for(int i = 0;i<rows;i++)
    {
        free(*(m+i));
    }
    free(m);
    free(r1);
    free(c1);
    free(r2);
    free(c2);
    return 0;
}
void find_active_bounding_box (int **m, int rows , int cols , int *r1 , int *c1 , int *r2 , int *c2)
{
    *r1 = rows;
    *c1 = cols;
    *r2 = -1;
    *c2 = -1;
    //those are obviously from AI
    for(int i = 0; i<rows; i++)
    {
        for(int j = 0; j<cols;j++)
        {
             if (m[i][j] != 0)
            {
                if (i < *r1)
                    *r1 = i;

                if (j < *c1)
                    *c1 = j;

                if (i > *r2)
                    *r2 = i;

                if (j > *c2)
                    *c2 = j;
            }
        }
    }
}
