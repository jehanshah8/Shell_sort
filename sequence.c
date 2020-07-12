#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

int static power(int base, int power);
void static print_seq(long *seq, int seq_size);

long *Generate_2p3q_Seq(int length, int *seq_size)
{
    // just to b safe
    *seq_size = 0; 
    // calculates the height of the 2p3q triangle needed
    int height = 0;
    while (power(3, height) <= length)
    {
        height++;
    }
    //printf("height = %d\n", height);

    // calculates size of 2p3q sequence upto but not including
    // the last level of the triangle
    for (int i = 0; i < height; i++)
    {
        *seq_size += 1 + i;
    }
    //printf("seq_size upto second to last layer = %d\n", *seq_size);

    // calculates how many 2p3q numbers from the last level of the
    // traingle are needed and adds to sequence size
    int num = power(2, height - 1);
    for (int i = 1; num < length; i++)
    {
        (*seq_size) += 1;
        num = power(2, height - i) * power(3, i);
    }
    //printf("total seq_size = %d\n", *seq_size);

    // allocate memory and fill up the sequence array
    long *seq = malloc(sizeof(*seq) * (*seq_size));
    if (seq == NULL)
    {
        *seq_size = 0; 
        return NULL;
    }

    if (*seq_size > 0)
    {
        seq[0] = 1;
        height = 1;
        int p2 = height;
        int p3 = 0;

        int i = 1;
        while (i < *seq_size)  
        {
            if (p3 > 1)
            {
                //printf("p2: %d, p3: %d\n", p2 + 3, p3 - 2);
                seq[i] = power(2, p2 + 3) * power(3, p3 - 2);
                i++;
            }

            if (power(2, p2) * power(3, p3) > seq[i - 1])
            {
                //printf("p2: %d, p3: %d\n", p2, p3);
                seq[i] = power(2, p2) * power(3, p3);
                i++;
            }

            if (p2 == 0)
            {
                height++;
                p2 = height;
                p3 = 0;
            }
            else
            {
                p2--;
                p3++;
            }
        }
    }

    print_seq(seq, *seq_size);
    return seq;
}

int static power(int base, int power)
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

void static print_seq(long *seq, int seq_size)
{
    printf("seq_size = %d\n", seq_size);
    for (int i = 0; i < seq_size; i++)
    {
        printf("%ld ", seq[i]);
    }
    printf("\n");
}
