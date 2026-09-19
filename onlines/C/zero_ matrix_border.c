#include #include
void zero_matrix_borders(int **m, int rows, int cols);
int main(void)
{
    int rows, cols;
    scanf("%d %d", &rows,& cols);
    if (rows < 1 || cols < 1)
    {
        return 1;
    }
    int **m;
    m = malloc(rows * sizeof(int *));
    if (m == NULL)
    {
        return 1;
    }
    for (int i = 0; i < rows; i++)
    {
        *(m + i) = malloc(cols * sizeof(int));
        if (*(m + i) == NULL)
        {
            return 1;
        }
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", *(m + i) + j);
        }
    }
    zero_matrix_borders(m, rows, cols); //argument
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", *(*(m + i) + j));
        }
        printf("\n");
    }
    for (int i = 0; i < rows; i++) //release
    {
        free(m[i]);
    }
    free(m);
    return 0;
}

void zero_matrix_borders(int **m, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
            {
                *(*(m + i) + j) = 0;
            }
        }
    }
}
