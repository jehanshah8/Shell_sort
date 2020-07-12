#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "shell_array.h"

void static print_arr(long *arr, int size); 

int main(int argc, char **argv)
{
    if (argc == 4)
    {
        if (strcmp(argv[1], "-a") == 0) 
        {
            int size;
            long * arr = Array_Load_From_File(argv[2], &size);
            print_arr(arr, size);

            //double n_comp; 
            //Array_Shellsort(arr, size, &n_comp);
            print_arr(arr, size);
            
            int successful_wites = Array_Save_To_File(argv[3], arr, size);
            printf("successfull writes = %d\n", successful_wites);
            
            free(arr);
            //printf("%le\n", n_comp);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

void static print_arr(long *arr, int size) 
{
    for (int i = 0; i < size; i++)
    {
        printf("%ld ", arr[i]); 
    }
    printf("\n"); 
}