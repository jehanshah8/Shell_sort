#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "sequence.h"

typedef struct List
{
    Node *node;
    Node *tail; 
    struct List *next;
} List;

static Node *insert_node(Node *last, long key);
static int calc_size(Node *head);
static List *create_sub_lists(Node *head, int size, long k);
static List *insert_list(List *list_tail, Node *nd);
static Node *insertion_sort(Node *list, double *n_comp);
static void print_sub_lists(List *sub_lists);
static Node *merge_sub_lists(List *sub_lists, long k);
static void empty_sub_lists(List **sub_lists);

Node *List_Load_From_File(char *filename)
{
    FILE *in_file_ptr = NULL;
    in_file_ptr = fopen(filename, "rb");

    // check if file was opened successfully
    if (in_file_ptr == NULL)
    {
        return NULL;
    }

    fseek(in_file_ptr, 0L, SEEK_END);
    int size = ftell(in_file_ptr) / sizeof(long);
    //printf("file size = %d\n", *size);
    rewind(in_file_ptr);

    long key;
    int nums_read = 0;
    Node *head = NULL;
    nums_read += fread(&key, sizeof(long), 1, in_file_ptr);
    head = insert_node(head, key);
    Node *tail = head;

    for (int i = 1; i < size; i++)
    {
        nums_read += fread(&key, sizeof(long), 1, in_file_ptr);
        tail = insert_node(tail, key);
    }
    printf("numbers read = %d\n", nums_read);
    fclose(in_file_ptr);
    return head;
}

static Node *insert_node(Node *tail, long key)
{
    // create a new node
    Node *nd = malloc(sizeof(*nd));
    if (nd == NULL)
    {
        return NULL;
    }
    *nd = (Node){.value = key, .next = NULL};

    // link it to last if last exists
    if (tail != NULL)
    {
        tail->next = nd;
    }
    // if last was NULL then return the newly created node
    return nd;
}

int List_Save_To_File(char *filename, Node *list)
{
    int successful_writes = 0;
    FILE *out_file_ptr = fopen(filename, "wb");

    if (out_file_ptr == NULL)
    {
        return -1;
    }

    //printf("size = %d", size);
    while (list != NULL)
    {
        successful_writes += fwrite(&(list->value), sizeof(long), 1, out_file_ptr);
        list = list->next;
    }
    fclose(out_file_ptr);
    return successful_writes;
}

static void print_list(Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%ld ", curr->value);
        curr = curr->next;
    }
    printf("\n\n");
}

Node *List_Shellsort(Node *list, double *n_comp)
{
    int size = calc_size(list);
    int seq_size;
    long *seq = Generate_2p3q_Seq(size, &seq_size);

    //printf("starting to sort\n");
    *n_comp = 0;
    
    List *sub_lists; 
    List *curr_list;
    // for all k in 2p3q
    printf("k =");
    for (int i = seq_size - 1; i >= 1; i--)
    {
        printf(" %ld", seq[i]);
        // for a particular k
        // form the sub-lists
        sub_lists = create_sub_lists(list, size, seq[i]);
        
        // unsorted sub-lists
        //printf("unsorted sub-lists\n"); 
        //print_sub_lists(sub_lists);

        // sort the sub list
        curr_list = sub_lists;
        while (curr_list != NULL)
        {
            //printf("before\n");
            //print_list(curr_list->node);
            curr_list->node = insertion_sort(curr_list->node, n_comp);
            //printf("after\n");
            //print_list(curr_list->node);
            curr_list = curr_list->next;
        }

        // sorted sub-lists
        //printf("sorted sub-lists\n"); 
        //print_sub_lists(sub_lists);

        // put them back together
        list = merge_sub_lists(sub_lists, seq[i]);
        //print_list(list);
    }
    insertion_sort(list, n_comp);
    printf("\nsort finished\n\n");

    free(seq);
    return list;
}

static int calc_size(Node *head)
{
    int size = 0;
    Node *curr = head;
    while (curr != NULL)
    {
        size++;
        curr = curr->next;
    }
    return size;
}

static List *create_sub_lists(Node *head, int size, long k)
{
    List *list = NULL;
    Node *curr_nd = head;
    Node *temp = curr_nd->next;
    curr_nd->next = NULL;
    list = insert_list(list, curr_nd);
    curr_nd = temp;
    List *curr_list = list;

    for (int i = 1; i < k; i++)
    {
        temp = curr_nd->next;
        curr_nd->next = NULL;
        curr_list = insert_list(curr_list, curr_nd);
        curr_nd = temp;
    }
    //print_sub_lists(list);

    int i = k - 1;
    //Node *temp2 = NULL;
    while (curr_nd != NULL)
    {
        //printf("i: %d\n", i);
        // point back to list head
        if (i % (k - 1) == 0)
        {
            //printf("looping around\n");
            curr_list = list;
        }

        //printf("inserting %ld...\n", curr_nd->value);

        //traverse sublist to find empty spot
        /*temp = curr_list->node;
        //printf("temp %ld ...", temp->value);
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        */
        temp = curr_nd->next;
        curr_nd->next = NULL;
        curr_list->tail->next = curr_nd;
        curr_list->tail = curr_list->tail->next; 
        curr_nd = temp;

        //printf("next node %ld...", curr_nd->value);
        curr_list = curr_list->next;
        //printf("next temp %ld ...", curr_list->node->value);
        i++;
    }
    //print_sub_lists(list);
    //printf("finished\n");
    return list;
}

static List *insert_list(List *list_tail, Node *nd)
{
    // create a new list
    List *list = malloc(sizeof(*list));
    if (list == NULL)
    {
        return NULL;
    }
    *list = (List){.node = nd, .tail = nd, .next = NULL};

    // link it to last if last exists
    if (list_tail != NULL)
    {
        list_tail->next = list;
    }
    // if last was NULL then return the newly created list
    return list;
}

static void print_sub_lists(List *sub_lists)
{
    List *curr_list = sub_lists;
    Node *curr_nd = NULL;
    int i = 0;
    while (curr_list != NULL)
    {
        printf("list %d: \n", i);
        curr_nd = curr_list->node;
        while (curr_nd != NULL)
        {
            printf("%ld ", curr_nd->value);
            curr_nd = curr_nd->next;
        }
        printf("\n");
        curr_list = curr_list->next;
        i++;
    }
    printf("\n");
}

static Node *insertion_sort(Node *head, double *n_comp)
{
    Node *sorted = NULL;
    Node *curr = head;
    Node *next = NULL;
    Node *temp = NULL;
    while (curr != NULL)
    {
        next = curr->next;

        *n_comp += 1;
        if (sorted == NULL || sorted->value >= curr->value)
        {
            curr->next = sorted;
            sorted = curr;
        }
        else
        {
            temp = sorted;
            *n_comp += 1;
            while (temp->next != NULL && temp->next->value < curr->value)
            {
                *n_comp += 1;
                temp = temp->next;
            }
            curr->next = temp->next;
            temp->next = curr;
        }

        curr = next;
    }
    return sorted;
}

static Node *merge_sub_lists(List *sub_lists, long k)
{
    List *curr_list = sub_lists;
    Node *temp = curr_list->node->next;
    curr_list->node->next = NULL;
    Node *head = curr_list->node;
    curr_list->node = temp;
    Node *curr_nd = head;
    curr_list = curr_list->next;

    int i = 1;
    while (curr_list->node != NULL)
    {
        temp = curr_list->node->next;
        curr_list->node->next = NULL;
        curr_nd->next = curr_list->node;
        curr_list->node = temp;
        //print_list(head);
        curr_nd = curr_nd->next;
        curr_list = curr_list->next;

        // loop around and point back to list head
        if (i % (k - 1) == 0)
        {
            //printf("looping around\n");
            curr_list = sub_lists;
        }
        i++;
    }
    //print_list(head);
    //printf("emptying sublists\n");
    empty_sub_lists(&sub_lists);
    return head;
}

static void empty_sub_lists(List **sub_lists)
{
    List *temp;
    while (*sub_lists != NULL)
    {
        temp = (*sub_lists)->next;
        (*sub_lists)->next = NULL;
        free(*sub_lists);
        *sub_lists = temp;
    }
    *sub_lists = NULL;
}
