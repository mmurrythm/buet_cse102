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
```c

```

This is a **dynamic jagged-array problem**, and the alignment rule is the key part. Let's turn it into a clean C solution and understand the pointer logic.

## 1. Understand the alignment

Suppose:

```text
a has 3 rows
b has 2 rows
```

Bottom-align them:

```text
a:       A0
         A1  ←→ B0
         A2  ←→ B1
```

So the row mapping is:

```c
bRow = i - (rA - rB)
```

for rows where they overlap.

But there is an even easier way:

```c
ia = rA - 1;
ib = rB - 1;
io = rOut - 1;
```

Start from the **bottom** and move upward.

---

# 2. Determine `rOut`

Because we are bottom-aligning the arrays, the output must contain enough rows for the taller array:

```c
rOut = (rA > rB) ? rA : rB;
```

Example:

```text
rA = 3
rB = 2

rOut = 3
```

---

# 3. Determine each output row length

For an aligned pair:

```text
a row: [3 4 5]
b row: [10 20 30]
```

the output length is:

```c
max(lengthA, lengthB)
```

If only one array has that row, simply copy its length.

So:

```c
cOut = (cA > cB) ? cA : cB;
```

---

# 4. Determine each output cell

For column `j`:

### Both exist

```c
out[j] = a[j] + b[j];
```

### Only `a` exists

```c
out[j] = a[j];
```

### Only `b` exists

```c
out[j] = b[j];
```

Since columns are **left-aligned**, there is no column offset.

---

# 5. Complete C solution

This version uses dynamically allocated jagged arrays and frees everything.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int rA, rB, rOut;

    int **a, **b, **out;
    int *cA, *cB, *cOut;

    /* =========================
       Read array A
       ========================= */

    scanf("%d", &rA);

    a = malloc(rA * sizeof(int *));
    cA = malloc(rA * sizeof(int));

    for (int i = 0; i < rA; i++)
    {
        scanf("%d", &cA[i]);

        a[i] = malloc(cA[i] * sizeof(int));

        for (int j = 0; j < cA[i]; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    /* =========================
       Read array B
       ========================= */

    scanf("%d", &rB);

    b = malloc(rB * sizeof(int *));
    cB = malloc(rB * sizeof(int));

    for (int i = 0; i < rB; i++)
    {
        scanf("%d", &cB[i]);

        b[i] = malloc(cB[i] * sizeof(int));

        for (int j = 0; j < cB[i]; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }

    /* =========================
       Determine output rows
       ========================= */

    rOut = (rA > rB) ? rA : rB;

    out = malloc(rOut * sizeof(int *));
    cOut = malloc(rOut * sizeof(int));

    /* =========================
       Build output
       ========================= */

    for (int io = 0; io < rOut; io++)
    {
        int ia = io - (rOut - rA);
        int ib = io - (rOut - rB);

        int hasA = (ia >= 0);
        int hasB = (ib >= 0);

        if (hasA && hasB)
        {
            cOut[io] = (cA[ia] > cB[ib])
                       ? cA[ia]
                       : cB[ib];
        }
        else if (hasA)
        {
            cOut[io] = cA[ia];
        }
        else
        {
            cOut[io] = cB[ib];
        }

        out[io] = malloc(cOut[io] * sizeof(int));

        for (int j = 0; j < cOut[io]; j++)
        {
            int existsA = hasA && (j < cA[ia]);
            int existsB = hasB && (j < cB[ib]);

            if (existsA && existsB)
            {
                out[io][j] = a[ia][j] + b[ib][j];
            }
            else if (existsA)
            {
                out[io][j] = a[ia][j];
            }
            else
            {
                out[io][j] = b[ib][j];
            }
        }
    }

    /* =========================
       Print output
       ========================= */

    printf("%d\n", rOut);

    for (int i = 0; i < rOut; i++)
    {
        printf("%d", cOut[i]);

        for (int j = 0; j < cOut[i]; j++)
        {
            printf(" %d", out[i][j]);
        }

        printf("\n");
    }

    /* =========================
       Free A
       ========================= */

    for (int i = 0; i < rA; i++)
    {
        free(a[i]);
    }

    free(a);
    free(cA);

    /* =========================
       Free B
       ========================= */

    for (int i = 0; i < rB; i++)
    {
        free(b[i]);
    }

    free(b);
    free(cB);

    /* =========================
       Free output
       ========================= */

    for (int i = 0; i < rOut; i++)
    {
        free(out[i]);
    }

    free(out);
    free(cOut);

    return 0;
}
```

## The most important part

This is the part you should understand for the exam:

```c
int ia = io - (rOut - rA);
int ib = io - (rOut - rB);
```

Suppose:

```text
rA = 3
rB = 2
rOut = 3
```

Then:

```text
io       ia       ib
----------------------
0        0       -1
1        1        0
2        2        1
```

Therefore:

```text
A0                 unmatched
A1        <---->   B0
A2        <---->   B1
```

Exactly what the question asks.

### Pointer/dynamic-memory picture

For a jagged array:

```c
int **a;
```

think:

```text
a
│
├── a[0] ──> [ 1 ][ 2 ]
│
├── a[1] ──> [ 3 ][ 4 ][ 5 ]
│
└── a[2] ──> [ 6 ][ 7 ][ 8 ][ 9 ]
```

There are **two levels of allocation**:

```c
a = malloc(rA * sizeof(int *));
```

allocates the row pointers.

Then:

```c
a[i] = malloc(cA[i] * sizeof(int));
```

allocates each individual row.

And therefore there are also **two levels of freeing**:

```c
free(a[i]);   // each row
free(a);      // row-pointer array
```

That's the core pattern for virtually every dynamically allocated jagged-array question.
