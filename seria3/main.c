#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <stdlib.h>

void naive_multiplication(double **A, double **B, double **C, int n, int m, int o) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < o; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void better_multiplication(double **A, double **B, double **C, int n, int m, int o) {

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            for (int j = 0; j < o; j++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void gsl_multiplication(double *A, double *B, double *C, int n, int m, int o, int p) {

    gsl_matrix_view a = gsl_matrix_view_array(A, n, m);
    gsl_matrix_view b = gsl_matrix_view_array(B, o, p);
    gsl_matrix_view c = gsl_matrix_view_array(C, n, p);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &a.matrix, &b.matrix, 0.0, &c.matrix);
}

int main(int argc, char const *argv[]) {
    clock_t start, end;
    srand(time(NULL));
    FILE *file = fopen("../result.csv", "w");

    fprintf(file, "Size,Naive,Better,BLAS\n");

    for (int i = 100; i < 1001; i = i + 100) {
        double **A = (double **) malloc(i * sizeof(double *));
        double **B = (double **) malloc(i * sizeof(double *));
        double **C = (double **) malloc(i * sizeof(double *));

        double *A_matrix = malloc(i * i * sizeof(double));
        double *B_matrix = malloc(i * i * sizeof(double));
        double *C_matrix = malloc(i * i * sizeof(double));

        for (int j = 0; j < i; j++) {
            A[j] = malloc(i * sizeof(double));
            B[j] = malloc(i * sizeof(double));
            C[j] = malloc(i * sizeof(double));
        }

        for (int j = 0; j < i; j++) {
            for (int k = 0; k < i; k++) {
                A[j][k] = (double) rand() / RAND_MAX;
                B[j][k] = (double) rand() / RAND_MAX;
                C[j][k] = 0.0;
            }
        }

        for (int j = 0; j < i * i; j++) {
            A_matrix[j] = (double) rand() / RAND_MAX;
            B_matrix[j] = (double) rand() / RAND_MAX;
            C_matrix[j] = 0.0;
        }

        start = clock();
        naive_multiplication(A, B, C, i, i, i);
        end = clock();
        fprintf(file, "%d,%f,", i, ((double) (end - start)) / CLOCKS_PER_SEC);

        start = clock();
        better_multiplication(A, B, C, i, i, i);
        end = clock();
        fprintf(file, "%f,", ((double) (end - start)) / CLOCKS_PER_SEC);

        start = clock();
        gsl_multiplication(A_matrix, B_matrix, C_matrix, i, i, i, i);
        end = clock();
        fprintf(file, "%f\n", ((double) (end - start)) / CLOCKS_PER_SEC);

        for (int j = 0; j < i; j++) {
            free(A[j]);
            free(B[j]);
            free(C[j]);
        }
        free(A);
        free(B);
        free(C);
        free(A_matrix);
        free(B_matrix);
        free(C_matrix);
    }

    fclose(file);

    return 0;
}


