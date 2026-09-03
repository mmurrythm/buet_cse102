/* ===================================================================
 *  CSE 102 - Offline 4 : IMAGE LAB
 * -------------------------------------------------------------------
 *  1. Rename this file to YOUR OWN roll number, e.g. 2505017.c
 *  2. Fill in every part marked   TODO
 *  3. Submit ONLY this one .c file.  Do not submit bmp.h or the images.
 *
 *  Compile:   gcc 2505000.c -o imagelab
 *  Run:       ./imagelab
 *
 *  bmp.h must be in the same folder as this file, and you must run the
 *  program from the folder that contains images/ .
 *
 *  READ THIS ONCE, IT SAVES YOU HOURS
 *  ----------------------------------
 *  An image here is just a table of numbers.  A 6 x 8 image is 6 rows
 *  and 8 columns, and every number is between 0 (black) and 255
 *  (white).  We store that table as  int **  :
 *
 *      int **m;                           m is a pointer to pointers
 *      m = malloc(rows * sizeof(int *));  one pointer per ROW
 *      m[i] = malloc(cols * sizeof(int)); the row itself
 *
 *  So m[i][j] is the pixel in row i, column j.  m[0][0] is top-left.
 *
 *  EVERY malloc must have a matching free.  That is why this program
 *  counts them: at the end, "Matrices created" and "Matrices
 *  destroyed" must be the SAME number, or you lose marks.
 * =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

/* -------------------------- global state ----------------------------- */

int  **image    = NULL;   /* the image currently in memory, or NULL      */
int    img_rows = 0;      /* its size.  Keep these two in step with      */
int    img_cols = 0;      /* whatever `image` actually points at!        */

int    alloc_count = 0;   /* +1 every time create_matrix succeeds        */
int    free_count  = 0;   /* +1 every time free_matrix is called         */

/* ======================= FUNCTIONS YOU MUST WRITE ==================== */

/* Allocate a rows x cols matrix and return it.
   Return NULL if rows or cols is not positive.
   Remember to do alloc_count++ when you succeed.                        */
int **create_matrix(int rows, int cols) //step 1
{
    /* TODO */
    // rows = number of rows pointers, cols = number of columns arrays
    int **m;
    if (rows < 1 || cols < 1) return NULL;
    m = malloc(rows * sizeof(int *));
    if (m == NULL) return NULL;
    for (int i = 0; i < rows; i++) 
    {
        m[i] = malloc(cols * sizeof(int));
        if (m[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }
    alloc_count++;
    return m;
}

/* Free every row, then free the array of row pointers.
   Do nothing if m is NULL.  Remember free_count++.                      */
void free_matrix(int **m, int rows)
{
    /* TODO */
    if (m == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
    free_count++;
}

/* Add `step` to every pixel, then keep it inside 0..255.               */
void brighten(int **m, int rows, int cols, int step)
{
    /* TODO */
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            m[i][j] += step;
            if (m[i][j] < 0) m[i][j] = 0;
            if (m[i][j] > 255) m[i][j] = 255;
        }
    }
}

/* Replace every pixel v by 255 - v.                                     */
void invert(int **m, int rows, int cols)
{
    /* TODO */
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            m[i][j] = 255 - m[i][j];
        }
    }
}

/* Pixels >= level become 255, the rest become 0.                        */
void apply_threshold(int **m, int rows, int cols, int level)
{
    /* TODO */
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if (m[i][j] >= level) {
                m[i][j] = 255;
            } else {
                m[i][j] = 0;
            }
        }
    }
}

/* Mirror left-right(cols/2), IN PLACE (swap columns j and cols-1-j).            */
void flip_horizontal(int **m, int rows, int cols)
{
    /* TODO */
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols / 2; j++) {
            int temp = m[i][j];
            m[i][j] = m[i][cols - 1 - j];
            m[i][cols - 1 - j] = temp;
        }
    }
}

/* Mirror top-bottom (rows/2), IN PLACE (swap rows i and rows-1-i).               */
void flip_vertical(int **m, int rows, int cols)
{
    /* TODO */
    for(int i = 0; i < rows/2; i++) {
        for(int j = 0; j < cols ; j++) {
            int temp = m[i][j];
            m[i][j] = m[rows-1-i][j];
            m[rows-1-i][j] = temp;
        }
    }
}

/* Build and return a NEW cols x rows matrix where out[j][i] = m[i][j].
   The caller is the one who frees the old matrix. (no allocation )              */
int **transpose(int **m, int rows, int cols)
{
    /* TODO */
    int **out = create_matrix(cols, rows);
    if (out == NULL) return NULL;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            out[j][i] = m[i][j]; //literally transpose 
        }
    }
    return out;
}

/* Build and return a NEW matrix holding rows r1..r2 and columns c1..c2
   (both ends included).  Write the new size into *out_rows / *out_cols.
   Return NULL if the region is invalid, and do not touch *out_rows or
   *out_cols in that case.                                               */
int **crop(int **m, int rows, int cols, int r1, int c1, int r2, int c2, int *out_rows, int *out_cols)
{
    /* TODO */
    if(r1 < 0 || c1 < 0 || r2 >= rows || c2 >= cols || r1 > r2 || c1 > c2) return NULL; //if this OR that true, reject.
    int nrows = r2 - r1 + 1;
    int ncols = c2 - c1 + 1;
    int **out = create_matrix(nrows, ncols);
    if (out == NULL) return NULL;
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            out[i][j] = m[r1 + i][c1 + j];
        }
    }
    *out_rows = nrows;
    *out_cols = ncols;
    return out;
}

/* Write the smallest pixel into *mn, the largest into *mx and the
   average into *mean.  This is how a function returns three answers:
   the caller passes the ADDRESS of its variables.                       */
void image_stats(int **m, int rows, int cols, int *mn, int *mx, double *mean)
{
    /* TODO */
    *mn = 255;
    *mx = 0;
    int  sum = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if (m[i][j] < *mn) *mn = m[i][j];
            if (m[i][j] > *mx) *mx = m[i][j];
            sum += m[i][j];
        }
    }
    *mean = (double)sum / (rows * cols); //double *mean
}

/* ====================== GIVEN TO YOU - DO NOT CHANGE ================= */

void show_menu(void)
{
    printf("\n+======================================+\n");
    printf("|            IMAGE  LAB                |\n");
    printf("|     Pointers , Pixels , Memory       |\n");
    printf("+======================================+\n");
    printf("1. Load image\n");
    printf("2. Show info\n");
    printf("3. Brighten\n");
    printf("4. Invert\n");
    printf("5. Threshold\n");
    printf("6. Flip horizontally\n");
    printf("7. Flip vertically\n");
    printf("8. Transpose\n");
    printf("9. Crop\n");
    printf("10. Save image\n");
    printf("11. Print matrix\n");
    printf("0. Exit\n");
}

/* ============================== main ================================= */

int main(void)
{
    int choice;

    show_menu();

    for (;;) {
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 0) break;

        switch (choice) {

        case 1:
        {    /* TODO: read a file name, ask bmp_get_size for its size,
                     throw away any image already loaded, create_matrix,
                     bmp_read_gray into it, update img_rows / img_cols.
                     Print:  Loaded <name>. Size: <rows> x <cols>
                     On failure: Error: could not open file <name>.     */

            char filename[100];
            if (scanf("%99s", filename) != 1) {
                printf("Error: invalid input.\n");
                break;
            }
            int old_rows = img_rows;
            int result = bmp_get_size(filename, &img_rows, &img_cols);
            if (result == 0) {
                printf("Error: could not open file %s.\n", filename);
                break;
            }

            if (image != NULL) {
                free_matrix(image, old_rows);
            }

            image = create_matrix(img_rows, img_cols);
            if (image == NULL || !bmp_read_gray(filename, image, img_rows, img_cols)) {
                printf("Error: could not open file %s.\n", filename);
                if (image != NULL) {
                    free_matrix(image, img_rows);
                    image = NULL;
                }
            } else {
                printf("Loaded %s. Size: %d x %d\n", filename, img_rows, img_cols);
            }
            break;
        }
        case 2:
        {    /* TODO: call image_stats and print the two info lines.      */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            else {
                int mn, mx;
                double mean;
                image_stats(image, img_rows, img_cols, &mn, &mx, &mean);
                printf("Size: %d x %d\n", img_rows, img_cols);
                printf("Min: %d  Max: %d  Mean: %.2f\n", mn, mx, mean);
            }
            break;
        }
        case 3:
        {    /* TODO: read k, call brighten, print: Brightened by k.      */
            int k;
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            if(scanf("%d", &k) != 1) {
                printf("Error: invalid input.\n");
                break;
            }

            brighten(image, img_rows, img_cols, k);
            printf("Brightened by %d.\n", k);
            break;
        }
        case 4:
            /* TODO: invert, print: Inverted.                            */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            invert(image, img_rows, img_cols);
            printf("Inverted.\n");
            break;
        
        case 5:
        {    /* TODO: read t, apply_threshold, print:
                     Thresholded at level t.                             */
            int t;
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            if(scanf("%d", &t) != 1) {
                printf("Error: invalid input.\n");
                break;
            }
            apply_threshold(image, img_rows, img_cols, t);
            printf("Thresholded at level %d.\n", t);
            break;
        }
        case 6:
            /* TODO: flip_horizontal, print: Flipped horizontally.       */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            flip_horizontal(image, img_rows, img_cols);
            printf("Flipped horizontally.\n");
            break;

        case 7:
            /* TODO: flip_vertical, print: Flipped vertically.           */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            flip_vertical(image, img_rows, img_cols);
            printf("Flipped vertically.\n");
            break;

        case 8:
        {    /* TODO: transpose into a NEW matrix, free the OLD one,
                     point `image` at the new one, and SWAP img_rows and
                     img_cols.  Print: Transposed. New size: R x C       */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            int **nimage = transpose(image, img_rows, img_cols);
            if(nimage == NULL) {
                printf("Error: could not transpose image.\n");
                break;
            }
            free_matrix(image, img_rows);
            image = nimage;
            int temp = img_rows;
            img_rows = img_cols;
            img_cols = temp;
            printf("Transposed. New size: %d x %d\n", img_rows, img_cols);
            break;
        }
        case 9:
        {    /* TODO: read r1 c1 r2 c2, crop into a NEW matrix, free the
                     OLD one, update img_rows / img_cols.
                     On failure: Error: invalid crop region.             */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            int r1, c1, r2, c2;
            if(scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4) {
                printf("Error: invalid input.\n");
                break;
            }
            int nrows, ncols;
            int** nimage = crop(image, img_rows, img_cols, r1, c1, r2, c2, &nrows, &ncols);
            if(nimage == NULL) {
                printf("Error: invalid crop region.\n");
                break;
            }
            free_matrix(image, img_rows);
            image = nimage;
            img_rows = nrows;
            img_cols = ncols;
            printf("Cropped. New size: %d x %d\n", img_rows, img_cols);
            break;
        }
        case 10:
        {    /* TODO: read a file name, bmp_write_gray, print:
                     Saved as <name>                                     */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            char save_filename[100];
            if(scanf("%99s", save_filename) != 1) {
                printf("Error: invalid input.\n");
                break;
            }
            int result = bmp_write_gray(save_filename, image, img_rows, img_cols);
            if(result) {
                printf("Saved as %s\n", save_filename);
            } else {
                printf("Error: could not save image.\n");
            }
            break; 
        }
        case 11:
            /* TODO: print the matrix with printf("%4d", ...) if it is
                     at most 16 x 16, otherwise:
                     Error: image too large to print.                    */
            if(image == NULL) {
                printf("Error: no image loaded.\n");
                break;
            }
            if(img_rows <= 16 && img_cols <= 16) {
                for(int i = 0; i < img_rows; i++) {
                    for(int j = 0; j < img_cols; j++) {
                        printf("%4d", image[i][j]);
                    }
                    printf("\n");
                }
            } else {
                printf("Error: image too large to print.\n");
            }
            break;

        default:
            printf("Error: invalid choice.\n");
            break;
        }
    }

    /* TODO: free the image that is still loaded, if any. */
    free_matrix(image, img_rows);
    printf("\nMatrices created: %d\n", alloc_count);
    printf("Matrices destroyed: %d\n", free_count);
    printf("Memory check: %s\n", (alloc_count == free_count) ? "OK" : "LEAK");
    printf("Goodbye!\n");
    return 0;
}
