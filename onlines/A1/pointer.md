# Problem 1 (8 Marks)
- Write a C function to swap two integer values.
```c
 void swap(int *a, int *b);
```
That swaps the values of integers pointed by pointer a and b.
### Use this function to sort three integers.
Write a main() function to
- take three integers x, y, z as input.
- sort x, y, z in increasing order using the swap() function.
- print x, y, z
Input format
Single line containing three space separated integers: x, y, z respectively.
Output format
Single line containing x, y, z separated by spaces.
## Solution
```c
#include<stdio.h>
#include<stdlib.h>

 void swap(int *a, int *b);
 int main(void)
 {
    int *a = malloc(3*sizeof(int));
    int i = 0;
    while(i<3)
    {
        scanf("%d ",a + i);
        i++;
    }
    i = 0;
    while(i<3)
    {
        int j = i + 1;
        while(j < 3)
        {
            if( *(a + i) > *(a + j)) swap(a + i,a + j);
            j++;
        }
        i++;
    }
    i = 0;
    while(i<3)
    {
        printf("%d ",*(a + i));
        i++;
    }
    free(a);
    
    return 0;
 }

 void swap(int *a, int *b)
 {
    int t;
    t = *a;
    *a = *b;
    *b = t;
    t = 0;
 }
```
# Problem 2 (12 Marks)
- Jagged array
### A jagged 2D array is an array of rows where each row can have a different number of columns (unlike a
normal matrix, where every row has the same number of columns).
Example jagged array with 3 rows:
- Row 0: [1, 2]
- Row 1: [3, 4, 5]
- Row 2: [6, 7, 8, 9]
Row 0 has 2 elements, Row 1 has 3, Row 2 has 4 — each row's length is independent.
Task
Take input two jagged integer arrays a and b, and produce a new jagged array out by aligning a and
b at their bottom-left cell and summing overlapping positions.
### Alignment rule:
1. Row alignment (vertical): The bottom row of a lines up with the bottom row of b. Move
upward one row at a time from there. If one array has more rows than the other, its extra rows sit
at the top with no counterpart in the other array.
2. Column alignment (horizontal): for each pair of aligned rows, column 0 (leftmost) of a’s row
lines up with column 0 of b’s row. Move rightward one column at a time from there. If one row
is longer, its extra rightmost cells have no counterpart.
### Combining:
1. If a cell in out has a counterpart in both a and b -> sum them.
2. If a cell has a counterpart in only one array -> copy that value through unchanged
Worked example

| a | b | out |
| :--- | :--- | :--- |
| **Row0:** `[1, 2]` | *None* | `[1, 2]` -> unmatched, copied from a |
| **Row1:** `[3, 4, 5]` | **Row0:** `[10, 20, 30]` | `[13, 24, 35]` -> 3+10, 4+20, 5+30 |
| **Row2:** `[6, 7, 8, 9]` *(bottom)* | **Row1:** `[40, 50]` *(bottom)* | `[46, 57, 8, 9]` -> 6+40, 7+50, then 8 and 9 copied |

### Input format
- First line contains a single integer r_A, number of rows in a
- Next r_A lines contain that row’s length c_i, followed by c_i space-separated integers
- Next line contains a single integer r_B, number of rows in b
- Next r_B lines contain that row’s length c_j, followed by c_j space-separated integers
### Output format
- r_Out [number of rows in out]
- r_Out lines containing that row’s length c_k in out, followed by c_k integers, elements of out.
### Instructions
1. a, b, out must be dynamically allocated
2. All allocated memory must be freed before the program exits

## Solution

```c
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    int **a, **b, **out; //jagged pointers need 2d array
    int ra, rb, rout;
    int *cola, *colb, *colout;

    scanf("%d",&ra);

    a = malloc( ra * sizeof(int*));
    cola = malloc(ra * sizeof(int));
    for(int i =0; i<ra; i++)
    {
        scanf("%d", cola + i);
        *(a+ i )=malloc(*(cola + i) * sizeof(int));
        for(int j = 0; j<*(cola + i); j++)
        {
            scanf("%d", *(a + i)+j);
        }
    }

    scanf("%d",&rb);

    b = malloc( rb * sizeof(int*));
    colb = malloc(rb * sizeof(int));
    for(int i =0; i<rb; i++)
    {
        scanf("%d", colb + i);
        *(b+ i )=malloc(*(colb + i) * sizeof(int));
        for(int j = 0; j<*(colb + i); j++)
        {
            scanf("%d", *(b + i)+j);
        }
    }

    rout = (ra > rb)? ra:rb;

    out = malloc(rout * sizeof(int*));
    colout= malloc(rout * sizeof(int));
    for(int i0= 0; i0<rout; i0++)
    {
        int ia = i0 - (rout -ra);   //so that index can go upward from below
        int ib = i0 - (rout -rb);   //same

        int hasa = (ia >= 0);
        int hasb = (ib >= 0);

        if(hasa && hasb)
        {
            *(colout+i0) = (*(cola+ia) > *(colb+ib))? *(cola+ia) : *(colb+ib);
        }
        else
        {
            *(colout+i0) = (hasa)? *(cola+ia) : *(colb+ib);
        }

        out[i0] = malloc(*(colout+i0) * sizeof(int));
        for(int j = 0; j< *(colout+i0); j++)
        {
            int exista = hasa && (j < *(cola+ia));
            int existb = hasb && (j < *(colb+ib));

            if(exista && existb)
            {
                *(*(out+i0)+j) = *(*(a+ia)+j) + *(*(b+ib)+j);
            }
            else
            {
                *(*(out+i0)+j) =(exista)? *(*(a+ia)+j) : *(*(b+ib)+j);
            }
        }
    }
    printf("%d\n", rout);

    for(int i = 0; i<rout; i++)
    {
        printf("%d", *(colout+i));
        for(int j = 0; j < *(colout+i); j++)
        {
            printf(" %d",*(*(out+i)+j));
        }
        printf("\n");
    }

    for(int i=0; i <ra; i++)
    {
        free(*(a+i));
    }

    free(a);
    free(cola);
    for(int i=0; i <rb; i++)
    {
        free(*(b+i));
    }

    free(b);
    free(colb);

    for(int i=0; i <rout; i++)
    {
        free(*(out+i));
    }

    free(out);
    free(colout);

    return 0;
}

```
