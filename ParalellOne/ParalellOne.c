#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#pragma warning(disable : 4996)


void usage() {
    printf("Invalid parameters!\n");
    printf("Enter the file name (or path if the input file is in a separate directory),\n");
    printf("followed by the number of rows (or columns) of the N*N matrix!\n");
    printf("The two inputs must be separated with a SPACE!\n\n");
}

void check_args(int argc) {
    if (argc != 3) {
        usage();
        exit(1);
    }
}

void load_matrix_to_buffer(float *buffer, int size, char *file_path) {

    float value = 0;
    int i;

    FILE* fp;
    fp = fopen(file_path, "r");
    if (fp == NULL) {   // Check null pointer
        usage();
        exit(1);
    }
    for (i = 0; i < size * size; i++) {
        fscanf(fp, "%f", &value);
        buffer[i] = value;
    }
    printf("Matrix item count: %d", i);
}

float get_max(float *buffer, int size,int *row_index, int *column_index) {
    float max = 0;
    int max_index = 0;
    int i;

    for (i = 0; i < (size * size); i++) {
        if (max < buffer[i] || max == 0) {
            max = buffer[i];
            max_index = i;
        }
    }
    
    *row_index = (int)(max_index / size);
    *column_index = (int)(max_index % size);

    return max;
}

void writeOutput(int row, int column, float max, double execution_time, double total_time) {
    FILE* fp;
    fp = fopen("output.txt", "w");

    fprintf(fp, "Results:");
    fprintf(fp, "\n\tRow index: %d", row);
    fprintf(fp, "\n\tColumn index: %d", column);
    fprintf(fp, "\n\tThe largest number: Matrix[%d][%d] = %f", row, column, max);
    fprintf(fp, "\n\nMaximum calculation time = %lf s", execution_time);
    fprintf(fp, "\nTotal execution time = %lf s", total_time);

    fclose(fp);

    printf("\n\nResults:");
    printf("\n\tRow index: %d", row);
    printf("\n\tColumn index: %d", column);
    printf("\n\tThe largest number: Matrix[%d][%d] = %f\n", row, column, max);
    printf("\nMaximum calculation time = %lf s", execution_time);
    printf("\nTotal execution time = %lf s\n", total_time);
}


int main(int argc, char* argv[]) {
    clock_t begin = clock();
    check_args(argc);

    int row_index, column_index;
    char* file_path = argv[1];
    int size = atoi(argv[2]);

    float* buffer = malloc(size * size * sizeof(float));
    load_matrix_to_buffer(buffer, size, file_path);

    clock_t begin_max = clock();
    float max = get_max(buffer, size, &row_index, &column_index);
    clock_t end_max = clock();
    clock_t end = clock();

    double execution_time = (double)(end_max - begin_max) / CLOCKS_PER_SEC;
    double total_time = (double)(end - begin) / CLOCKS_PER_SEC;

    writeOutput(row_index, column_index, max, execution_time, total_time);

    return 0;
}