//move pointer back to the head of the list
    //curr_list = list;
    int i = k - 1;
    int j = 0;
    int depth = 0;
    while (curr_nd != NULL)
    {
        printf("i: %d\n", i);
        // point back to list head
        if (i % (k - 1) == 0)
        {
            printf("looping around\n");
            curr_list = list;
            depth++;
        }
        else
        {
            printf("not looping\n");
        }

        printf("inserting %ld...", curr_nd->value);
        //traverse sublist to find empty spot
        temp = curr_list->node;
        printf("temp %ld ...", temp->value);

        /**
        j = 0;
        while (j < depth || temp->next != NULL)
        {
            temp = temp->next;
            j++;
        }
        temp->next = curr_nd;
        */
        curr_nd = curr_nd->next;
        printf("next node %ld...", curr_nd->value);
        curr_list = curr_list->next;
        printf("next temp %ld ...", curr_list->node->value);
        i++;
        printf("finished\n");
    }