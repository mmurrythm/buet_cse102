# Jagged 2D Array — Brief Error-Fixing Tutorial
---

## 1. Understand the structure first

A jagged array has different column counts per row:

```text
a
│
├── row 0 → [1 2]
├── row 1 → [3 4 5]
└── row 2 → [6 7 8 9]
```

Therefore:

```c
int **a;
int *cola;
```

- `a` → array of row pointers
- `cola` → stores each row's length

### Pointer cheat sheet

```text
a + i              → address of row pointer
*(a + i)           → row pointer
*(a + i) + j       → address of element
*(*(a+i) + j)      → element value

cola + i           → address of row length
*(cola + i)        → row length
```

---

# 2. Error: Wrong pointer type

### ❌ Wrong

```c
int *a;
```

### ✅ Correct

```c
int **a;
```

Because each `a[i]` is itself a pointer to a row.

---

# 3. Error: Wrong allocation size for row pointers

The outer array contains `int *`, not `int`.

### ❌

```c
a = malloc(ra * sizeof(int));
```

### ✅

```c
a = malloc(ra * sizeof(int *));
```

Think:

```text
a → [pointer] [pointer] [pointer]
```

not:

```text
a → [integer] [integer] [integer]
```

---

# 4. Allocating each jagged row

Each row can have a different size.

### ✅

```c
*(a+i) = malloc(*(cola+i) * sizeof(int));
```

Then input:

```c
scanf("%d", *(a+i)+j);
```

Equivalent ordinary notation:

```c
scanf("%d", &a[i][j]);
```

---

# 5. Error: Forgetting that `cola` stores ALL row sizes

Suppose:

```text
cola = [2, 3, 4]
```

Then:

```c
*cola
```

means only:

```text
2
```

### ❌ Wrong

```c
*cola > *colb
```

when you are processing arbitrary rows.

This compares only **row 0**.

### ✅ Correct

```c
*(cola+ia) > *(colb+ib)
```

because `ia` and `ib` tell you which rows are currently aligned.

---

# 6. Bottom alignment — the key trick

Suppose:

```text
A has 3 rows
B has 2 rows
```

Bottom-left alignment means:

```text
A:  A0
    A1
    A2
B:      B0
        B1
```

Use:

```c
int ia = i0 - (rout-ra);
int ib = i0 - (rout-rb);
```

Example:

```text
rout = 3
ra   = 3
rb   = 2

i0:    0   1   2
ia:    0   1   2
ib:   -1   0   1
```

`-1` means **no corresponding row**.

---

# 7. Error: Accessing a nonexistent row

If:

```c
ib = -1;
```

you must NOT blindly do:

```c
*(b+ib)
```

because that means:

```c
*(b-1)
```

which is invalid.

So create existence flags:

```c
int hasa = (ia >= 0);
int hasb = (ib >= 0);
```

---

# 8. Why this works safely

You used:

```c
int exista = hasa && (j < *(cola+ia));
```

This is good.

Why?

C's `&&` is **short-circuiting**.

If:

```c
hasa == 0
```

then C doesn't evaluate:

```c
j < *(cola+ia)
```

So an `ia == -1` doesn't cause an access.

### Memory rule

> **Check existence before accessing the row.**

---

# 9. Output row length

For aligned rows:

```c
max(length A, length B)
```

### ✅

```c
*(colout+i0) =
    (*(cola+ia) > *(colb+ib))
    ? *(cola+ia)
    : *(colb+ib);
```

If only A exists:

```c
*(colout+i0) = *(cola+ia);
```

If only B exists:

```c
*(colout+i0) = *(colb+ib);
```

---

# 10. Cell calculation

There are exactly **3 cases**.

### Both exist

```c
if(exista && existb)
{
    *(*(out+i0)+j) =
        *(*(a+ia)+j) + *(*(b+ib)+j);
}
```

### Only one exists

```c
else
{
    *(*(out+i0)+j) =
        (exista) ? *(*(a+ia)+j)
                 : *(*(b+ib)+j);
}
```

Remember:

```text
A + B → add
A only → copy A
B only → copy B
```

---

# 11. Error: Printing `colout` instead of its value

### ❌

```c
for(int j = 0; j < colout; j++)
```

`colout` is:

```c
int *
```

### ✅

```c
for(int j = 0; j < *(colout+i); j++)
```

because `*(colout+i)` is the current row's length.

---

# 12. Error: Printing an address instead of a value

For a 2D pointer:

### ❌

```c
printf("%d", *(out+i)+j);
```

This is an **address**.

### ✅

```c
printf("%d", *(*(out+i)+j));
```

This is the **actual integer**.

---

# 13. Error: Wrong `free()`

Remember:

```c
a
 ↓
[row pointer] → [row data]
```

Therefore:

### ✅ Free each row

```c
for(int i=0; i<ra; i++)
    free(*(a+i));
```

Then:

```c
free(a);
free(cola);
```

Same for `b` and `out`.

### Golden rule

```text
malloc row       → free(row)
malloc outer     → free(outer)
```

---

# 14. Your final memory map

```text
int **a
   │
   ├── a+0 ──→ pointer ──→ [A A]
   │
   ├── a+1 ──→ pointer ──→ [B B B]
   │
   └── a+2 ──→ pointer ──→ [C C C C]

int *cola
   │
   └── [2] [3] [4]
        ↑   ↑   ↑
       row0 row1 row2
```

---

# 🧠 Sessional Cheat Sheet

When solving this question, follow this order:

```text
1. int **a, **b, **out
        ↓
2. Allocate outer pointer arrays
        ↓
3. Allocate each row separately
        ↓
4. Store row lengths in cola/colb
        ↓
5. rout = max(ra, rb)
        ↓
6. Map bottom rows:
   ia = i0 - (rout-ra)
   ib = i0 - (rout-rb)
        ↓
7. Check row existence
        ↓
8. Find output row length
        ↓
9. For each column:
      both → add
      A only → copy A
      B only → copy B
        ↓
10. Print using *(colout+i)
        ↓
11. Free every row
        ↓
12. Free outer arrays
```

### ⭐ The 5 mistakes to watch for

| Mistake | Correct |
|---|---|
| `int *a` | `int **a` |
| `malloc(ra*sizeof(int))` for outer array | `malloc(ra*sizeof(int *))` |
| `*cola` for arbitrary row | `*(cola+ia)` |
| `*(a+i)+j` when you need value | `*(*(a+i)+j)` |
| `j < colout` | `j < *(colout+i)` |

**Most important idea:**  
> `int **` gives you **rows of pointers**, and each row points to its own dynamically allocated array. Then `ia/ib` solve the vertical alignment, while `exista/existb` solve the horizontal mismatch.
