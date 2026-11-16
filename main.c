
#include "header.h"

int main(int argc, char *argv[])
{
    // For CLA validation
    if(validate_ip(argv, argc) == FAILURE)
    {
        return FAILURE;
    }

    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    // [CHANGED] Sign variables
    int sign1 = 0;
    int sign2 = 0;

    char *str = argv[1];
    char *str1 = argv[3];

    // [CHANGED] Extract signs
    if(str[0] == '-')
    {
        sign1 = 1;
        str++;
    }
    else if(str[0] == '+')
    {
        str++;
    }

    if(str1[0] == '-')
    {
        sign2 = 1;
        str1++;
    }
    else if(str1[0] == '+')
    {
        str1++;
    }

    // Insert first operand into DLL
    int i = 0;

    while(str[i] != '\0')
    {
        int data = str[i] - '0';

        if(dl_insert_last_for_list1(&head1, &tail1, data) == FAILURE)
        {
            printf("Insertion of data in list fails\n");
            return FAILURE;
        }

        i++;
    }

    // Insert second operand into DLL
    int j = 0;

    while(str1[j] != '\0')
    {
        int data = str1[j] - '0';

        if(dl_insert_last_for_list1(&head2, &tail2, data) == FAILURE)
        {
            printf("Insertion of data in list fails\n");
            dl_delete_list(&head1, &tail1);
            return FAILURE;
        }

        j++;
    }

    // [CHANGED] Remove leading zeros
    remove_leading_zeros(&head1, &tail1);
    remove_leading_zeros(&head2, &tail2);

    // Negative zero is treated as positive zero
    if(head1->data == 0)
        sign1 = 0;

    if(head2->data == 0)
        sign2 = 0;

    print_list(head1);
    print_list(head2);

    // For addition/subtraction/multiplication/division
    Dlist *headR = NULL;
    Dlist *tailR = NULL;

    Dlist *headR1 = NULL;
    Dlist *tailR1 = NULL;

    int status = FAILURE;
    int negative = 0;

    // [CHANGED] ADDITION
    if(strcmp(argv[2], "+") == 0)
    {
        int compare = list_compare(&head1, &tail1,&head2, &tail2);

        if(sign1 == sign2)
        {
            // Same signs: Addition
            status = add(&head1, &tail1, &head2, &tail2,&headR, &tailR);

            negative = sign1;
        }
        else
        {
            // Different signs: Subtraction
            if(compare == list_1)
            {
                status = sub(&head1, &tail1, &head2, &tail2,&headR, &tailR);

                negative = sign1;
            }
            else if(compare == list_2)
            {
                status = sub(&head2, &tail2, &head1, &tail1, &headR, &tailR);

                negative = sign2;
            }
            else
            {
                status = dl_insert_first(&headR, &tailR, 0);
                negative = 0;
            }
        }

        if(status == SUCCESS)
        {
            remove_leading_zeros(&headR, &tailR);

            if(headR->data == 0)
                negative = 0;

            printf("Result of addition is:\n");
            print_result(headR, negative);
        }
    }

    // [CHANGED] SUBTRACTION
    else if(strcmp(argv[2], "-") == 0)
    {
        // A - B = A + (-B)
        int effective_sign2 = !sign2;

        int compare = list_compare(&head1, &tail1, &head2, &tail2);

        if(sign1 == effective_sign2)
        {
            // Same signs: Addition
            status = add(&head1, &tail1, &head2, &tail2, &headR, &tailR);

            negative = sign1;
        }
        else
        {
            // Different signs: Subtraction
            if(compare == list_1)
            {
                status = sub(&head1, &tail1, &head2, &tail2,&headR, &tailR);

                negative = sign1;
            }
            else if(compare == list_2)
            {
                status = sub(&head2, &tail2, &head1, &tail1, &headR, &tailR);

                negative = effective_sign2;
            }
            else
            {
                status = dl_insert_first(&headR, &tailR, 0);
                negative = 0;
            }
        }

        if(status == SUCCESS)
        {
            remove_leading_zeros(&headR, &tailR);

            if(headR->data == 0)
                negative = 0;

            printf("Result of subtraction is:\n");
            print_result(headR, negative);
        }
    }

    // [CHANGED] MULTIPLICATION
    else if(strcmp(argv[2], "*") == 0)
    {
        status = mult(&head1, &tail1, &head2, &tail2,&headR, &tailR, &headR1, &tailR1);

        if(status == SUCCESS)
        {
            negative = sign1 ^ sign2;

            remove_leading_zeros(&headR, &tailR);

            if(headR->data == 0)
                negative = 0;

            printf("Result of Multiplication is:\n");
            print_result(headR, negative);
        }
    }

    // [CHANGED] DIVISION
    else if(strcmp(argv[2], "/") == 0)
    {
        status = division(&head1, &tail1, &head2, &tail2,&headR, &tailR);

        if(status == SUCCESS)
        {
            negative = sign1 ^ sign2;

            remove_leading_zeros(&headR, &tailR);

            if(headR->data == 0)
                negative = 0;

            printf("Result of Division is:\n");
            print_result(headR, negative);
        }
    }

    if(status == FAILURE)
    {
        printf("Operation failed\n");
    }

    

    return status;
}
