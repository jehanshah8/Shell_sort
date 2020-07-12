#include <stdio.h>
#include <stdlib.h>

#include "sequence.h"

long *Array_Load_From_File(char *filename, int *size)
{
    FILE *in_file_ptr = NULL;
    in_file_ptr = fopen(filename, "rb");

    // check if file was opened successfully
    if (in_file_ptr == NULL)
    {
        *size = 0;
        return NULL;
    }

    fseek(in_file_ptr, 0L, SEEK_END);
    *size = ftell(in_file_ptr) / sizeof(long);
    //printf("file size = %d\n", *size);
    rewind(in_file_ptr);

    long *arr = malloc(sizeof(*arr) * (*size));
    if (arr == NULL)
    {
        fclose(in_file_ptr);
        *size = 0;
        return NULL;
    }

    int nums_read = 0;
    for (int i = 0; i < *size; i++)
    {
        nums_read += fread(arr + i, sizeof(*arr), 1, in_file_ptr);
    }
    //printf("numbers read = %d\n", nums_read);
    fclose(in_file_ptr);
    return arr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
    int successful_writes = 0;
    FILE *out_file_ptr = fopen(filename, "wb");
    if (out_file_ptr != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            successful_writes += fwrite(array + i, sizeof(*array), 1, out_file_ptr);
        }
    }
    fclose(out_file_ptr);
    return successful_writes;
}

void Array_Shellsort(long *array, int size, double *n_comp)
{
    int seq_size;
    long *seq = Generate_2p3q_Seq(size, &seq_size);

    for (int i = seq_size - 1; i >= 0; i--)
    {
        printf("%ld ", seq[i]);
        for (long j = seq[i]; j < size; j++) 
        {   
            long temp = array[j];
            long k = j; 
            while (k >= seq[i] && array[k - seq[i]] > temp) 
            {
                array[k] = array[k - seq[i]];
                k = k - seq[i]; 
            }
            array[k] = temp; 
        }
    }
    printf("\n");
    free(seq);
    return;
}