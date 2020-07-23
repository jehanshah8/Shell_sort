#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

static int power(int base, int power);
//static void print_seq(long *seq, int seq_size);

long *Generate_2p3q_Seq(int length, int *seq_size)
{
    // just to b safe
    *seq_size = 0;
    // calculates the height of the 2p3q triangle needed
    int height = 0;
    while (power(3, height) < length)
    {
        height++;
    }
    //printf("height = %d\n", height);

    int max_level = height;
    while (power(2, max_level + 1) < length)
    {
        max_level++;
    }
    //printf("max_level = %d\n", max_level);

    // calculates size of 2p3q sequence upto but not including
    // the last level of the triangle
    for (int i = 0; i < height; i++)
    {
        *seq_size += 1 + i;
    }
    //printf("seq_size upto second to last layer = %d\n", *seq_size);

    // calculate the size of numbers from the height to the max level
    long num = 0;
    int p2 = height;
    int p3 = 0;

    for (int i = height; i <= max_level; i++)
    {
        p2 = i;
        p3 = 0;
        while (p2 >= 0)
        {
            num = power(2, p2) * power(3, p3);
            if (num < length)
            {
                *seq_size += 1;
            }
            p2--;
            p3++;
        }
    }

    //printf("total seq_size = %d\n", *seq_size);

    // allocate memory and fill up the sequence array
    long *seq = malloc(sizeof(*seq) * (*seq_size));
    if (seq == NULL)
    {
        *seq_size = 0;
        return NULL;
    }

    // Peer Review: How to generate the sequence in ascending order so that I don't have to sort it later?
    // populate array
    if (*seq_size > 0)
    {
        int curr_level = 0;
        int i = 0;
        while (i < *seq_size)
        {
            //printf("-/%d/- \n{%d}", i, curr_level);
            p2 = curr_level;
            p3 = 0;
            while (p2 >= 0)
            {
                //check_next_level(seq, &i, p2, p3, length, max);
                num = power(2, p2) * power(3, p3);
                if (num < length)
                {
                    //printf("%ld ", num);
                    seq[i] = num;
                    i++;
                }
                p2--;
                p3++;
            }
            curr_level++;
        }
    }

    // sort the sequence.
    for (int i = 1; i < *seq_size; i++)
    {
        long temp = seq[i];
        long j = i;
        while (j >= 1 && seq[j - 1] > temp)
        {
            seq[j] = seq[j - 1];
            j--;
        }
        seq[j] = temp;
    }

    //print_seq(seq, *seq_size);
    //printf("\n");
    return seq;
}

static int power(int base, int power)
{
    if (base == 0)
    {
        return 0;
    }

    int result = 1;
    for (int i = 0; i < power; i++)
    {
        result *= base;
    }
    return result;
}

/**
static void print_seq(long *seq, int seq_size)
{
    printf("\nsequence: \n");
    for (int i = 0; i < seq_size; i++)
    {
        printf("%ld ", seq[i]);
    }
    printf("\n");
}
*/
