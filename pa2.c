#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "shell_array.h"
#include "sequence.h"

//void static print_arr(long *arr, int size);

int main(int argc, char **argv)
{
    if (argc == 4)
    {
        if (strcmp(argv[1], "-a") == 0)
        {
            /**
            int seq_size;
            int temp = 3000; 
            long *seq = Generate_2p3q_Seq(temp, &seq_size);
            free(seq);
            */
            int size;
            long *arr = Array_Load_From_File(argv[2], &size);
            //printf("before\n");
            //print_arr(arr, size);

            double n_comp;
            Array_Shellsort(arr, size, &n_comp);
            //printf("after\n");
            //print_arr(arr, size);
            
            Array_Save_To_File(argv[3], arr, size);
            //printf("successfull writes = %d\n", successful_wites);

            free(arr);
            printf("%le\n", n_comp);
            
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

/**
void static print_arr(long *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%ld ", arr[i]);
    }
    printf("\n");
}
*/