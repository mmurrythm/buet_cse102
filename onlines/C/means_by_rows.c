#include #include 
void get_row_means(int **m, int rows, int cols, double *out_means);
int main(void)
{
    int **arr;
    double *out_means;
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    if (rows <= 0 || cols <= 0)
    {
        printf("Error!");
        return 0;
    }
    else
    {
        arr = malloc(rows * sizeof(int *));
        if (arr == NULL)
        {
            printf("Error!");
            return 0;
        }
        for (int i = 0; i < rows; i++)
        {
            *(arr + i) = malloc(cols * sizeof(int));
            if (*(arr + i) == NULL)
            {
                printf("Error!");
                return 0;
            }
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                scanf("%d", *(arr + i) + j);
            }
        }
        out_means = malloc(rows * sizeof(double)); // output mem alloc
        if (out_means == NULL)
        {
            printf("Error!");
            return 0;
        }
        get_row_means(arr, rows, cols, out_means); // argument
        for (int i = 0; i < rows; i++)
        {
            printf("%.2lf", *(out_means + i));
            printf("\n");
        }
    }
    for (int i = 0; i < rows; i++) // release
    {
        free(*(arr + i));
    }
    free(arr);
    free(out_means);
    return 0;
}

void get_row_means(int **m, int rows, int cols, double *out_means)
{
    for (int i = 0; i < rows; i++)
    {
        double avg = 0;
        for (int j = 0; j < cols; j++)
        {
            avg += (double)(*(*(m + i) + j));
        }
        avg /= cols;
        *(out_means + i) = avg;
    }
}
