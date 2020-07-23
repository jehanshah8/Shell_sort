#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"
#include "sequence.h"

//static void print_arr(long *arr, int size);
//static bool is_sorted_arr(long* arr, int size);
//static void print_list(Node *head);
//static bool is_sorted_list(Node *head);
static void empty_list(Node **head);

int main(int argc, char **argv)
{
    if (argc == 4)
    {
        if (strcmp(argv[1], "-a") == 0)
        {
            /* uncomment to test generate independently
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
            //printf("successfull writes = %d\n", successful_writes);

            //bool works = is_sorted(arr, size);
            //printf("%s\n", works ? "true" : "false");
            free(arr);
            printf("%le\n", n_comp);

            return EXIT_SUCCESS;
        }
        else if (strcmp(argv[1], "-l") == 0)
        {
            Node *head = List_Load_From_File(argv[2]);
            //printf("before\n");
            //print_list(head);

            double n_comp;
            head = List_Shellsort(head, &n_comp);
            //printf("after\n");
            //print_list(head);

            List_Save_To_File(argv[3], head);
            //printf("successfull writes = %d\n", successful_writes);

            //bool works = is_sorted_list(head);
            //printf("%s\n", works ? "true" : "false");
            empty_list(&head);
            printf("%le\n", n_comp);

            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

/*
static void print_arr(long *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%ld ", arr[i]);
    }
    printf("\n");
}
*/

/*
static bool is_sorted_arr(long* arr, int size) {
    for(int i = 1; i < size; i++) {
        if(arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}
*/

static void empty_list(Node **head)
{
    Node *temp;
    while (*head != NULL)
    {
        temp = (*head)->next;
        free(*head);
        *head = temp;
    }
    *head = NULL;
}

/**
static void print_list(Node *head)
{
    while (head != NULL)
    {
        printf("%ld ", head->value);
        head = head->next;
    }
    printf("\n\n");
}
*/

/**
static bool is_sorted_list(Node *head)
{
    while (head->next != NULL)
    {
        if (head->value > head->next->value)
        {
            return false;
        }
        head = head->next;
    }
    return true;
}
*/
