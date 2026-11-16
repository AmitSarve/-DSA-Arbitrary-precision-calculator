#include "header.h"

/* [CHANGED] Validate optional + or - signs and digit-only magnitudes. */
int validate_ip(char *argv[], int argc)
{
    if (argc != 4)
    {
        printf("Error!!: ./a.out operand1 operator operand2\n");
        return FAILURE;
    }

    if (argv[2][1] != '\0' ||
        (argv[2][0] != '+' && argv[2][0] != '-' &&
         argv[2][0] != '*' && argv[2][0] != '/'))
    {
        printf("Invalid operator. Use +, -, * or /.\n");
        return FAILURE;
    }

    char *operands[2] = { argv[1], argv[3] };

    for (int k = 0; k < 2; k++)
    {
        int i = 0;

        if (operands[k][i] == '+' || operands[k][i] == '-')
            i++;

        /* Reject empty strings and a sign without digits. */
        if (operands[k][i] == '\0')
        {
            printf("Invalid operand: enter at least one digit.\n");
            return FAILURE;
        }

        for (; operands[k][i] != '\0'; i++)
        {
            if (!isdigit((unsigned char)operands[k][i]))
            {
                printf("Invalid operand: only signed integers are supported.\n");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}

int dl_insert_last_for_list1(Dlist**head, Dlist**tail, int data)
{
    Dlist*newNode=malloc(sizeof(Dlist));
    if(newNode==NULL)
    {
        return FAILURE;
    }
    
    newNode->data=data;
    newNode->prev=NULL;
    newNode->next=NULL;
    
    if(*head==NULL)
    {
        *head=newNode;
        *tail=newNode;
        return SUCCESS;
    }
    newNode->prev=(*tail);
    (*tail)->next=newNode;
    
    (*tail)=newNode;
    return SUCCESS;

}

//FOR ADDITION OPERATION
int add(Dlist** head1,Dlist** tail1,Dlist** head2, Dlist** tail2,Dlist** headR,Dlist** tailR)
{
    Dlist*temp1=(*tail1);
    Dlist*temp2=(*tail2);
    int carry=0;
    while(temp1!=NULL || temp2!=NULL)
    {
        
        if(temp1!=NULL && temp2!=NULL)
        {
            int data = (temp1->data) + (temp2->data) + carry ;

            int last_digit= data % 10;

            if(dl_insert_first(headR, tailR, last_digit)==FAILURE)
            {
                return FAILURE;
            }

            carry = data / 10;

            temp1=temp1->prev;
            temp2=temp2->prev;
        }
        else if(temp1==NULL && temp2!=NULL)
        {
            int data =  (temp2->data) + carry ;

            int last_digit= data % 10;

            if(dl_insert_first(headR, tailR, last_digit)==FAILURE)
            {
                return FAILURE;
            }

            carry = data / 10;

            temp2=temp2->prev;
        }
        else if(temp1!=NULL && temp2==NULL)
        {
            int data =  (temp1->data) + carry ;

            int last_digit= data % 10;

            if(dl_insert_first(headR, tailR, last_digit)==FAILURE)
            {
                return FAILURE;
            }

            carry = data / 10;

            temp1=temp1->prev;
        }
        
        }
        if(carry!=0)
        {
            if(dl_insert_first(headR, tailR, carry)==FAILURE)
            {
                
                return FAILURE;
            }
           
        }
        return SUCCESS;
    }


//FOR SUBTRACTION OPERATION
int sub(Dlist**head1 ,Dlist**tail1 ,Dlist**head2 , Dlist**tail2 ,Dlist**headR ,Dlist**tailR )
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    int borrow = 0;

    while(temp1 != NULL || temp2 != NULL)
    {
        int data;

        if(temp1 != NULL && temp2 != NULL)
        {
            data = temp1->data - temp2->data - borrow;

            if(data < 0)
            {
                data = data + 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if(temp1 != NULL && temp2 == NULL)
        {
            data = temp1->data - borrow;

            if(data < 0)
            {
                data = data + 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            temp1 = temp1->prev;
        }
        else
        {
            return FAILURE;
        }

        if(dl_insert_first(headR, tailR, data) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;

}

int list_compare(Dlist**head1,Dlist**tail1,Dlist**head2,Dlist**tail2)
{
    if(*head1 ==NULL && *head2==NULL)
    {
        return equal_list;
    }
    if(*head1==NULL)
    {
        return list_2;
    }
    if(*head2==NULL)
    {
        return list_1;
    }
    int count1=0;
    int count2=0;
    Dlist*temp1=(*head1);
    Dlist*temp2=(*head2);

    //to count nodes in list1 
    while(temp1!=NULL)
    {
        count1++;
        temp1=temp1->next;
    }

    // for to count nodes in list2
    while(temp2!=NULL)
    {
        count2++;
        temp2=temp2->next;
    }

    //check which num is bigger list1 or list2
    if(count1 > count2)
    {
        return list_1;
    }
    else if(count1 < count2)
    {
        return list_2;
    }
    else if(count1==count2)
    {
        if((*head1)->data > (*head2)->data )
        {
            return list_1;
        }
        else if((*head1)->data < (*head2)->data )
        {
            return list_2;
        }
        else if((*head1)->data == (*head2)->data )
        {
            Dlist*temp1=*head1;
            Dlist*temp2=*head2;
            while(temp1!=NULL && temp2!=NULL)
            {
                if(temp1->data > temp2->data)
                {
                    return list_1;                
                }
                else if(temp1->data < temp2->data)
                {
                    return list_2;
                }
                temp1=temp1->next;
                temp2=temp2->next;
            }
            return equal_list;
        }
    }
    return equal_list;

}
int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
   Dlist*temp=(*head);
    
    if(*head==NULL)
    {
        Dlist*newNode=malloc(sizeof(Dlist));
        if(newNode==NULL)
        {
            return FAILURE;
        }
        newNode->prev=NULL;
        newNode->data=data;
        newNode->next=NULL;
        
        (*head)=newNode;
        (*tail)=newNode;
        return SUCCESS;
    }
    
    Dlist*newNode=malloc(sizeof(Dlist));
    if(newNode==NULL)
    {
        return FAILURE;
    }
    newNode->prev=NULL;
    newNode->data=data;
    newNode->next=NULL;
    
    (*head)=newNode;
    temp->prev=newNode;
    newNode->next=temp;
    return SUCCESS;
}

void print_list(Dlist*head)
{
    //printf("list numbers is \n");

	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    printf("Head -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d  ", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		    if (head)
            {

		        printf("  ");
            }
	    }
    	printf(" <-Tail\n");
    }
}
void print_result(Dlist *head, int negative)
{
    /*while(head != NULL && head->data == 0 && head->next != NULL)
    {
        head = head->next;
    }*/

    if(negative && head != NULL)
    {
        printf("-");
    }

    while(head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

//FOR multiplication
int mult(Dlist**head1,Dlist**tail1,Dlist**head2,Dlist**tail2,Dlist** headR,Dlist** tailR,Dlist** headR1,Dlist** tailR1)
{
    Dlist *backuphead = NULL;
    Dlist *backuptail = NULL;

    int count = 0;

    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    while(temp2 != NULL)
    {
        int carry = 0;
        temp1 = *tail1;

        while(temp1 != NULL)
        {
            int data = (temp1->data * temp2->data) + carry;
            int last_digit = data % 10;
            carry = data / 10;

            if(count==0)
            {
                // First multiplication
                if(dl_insert_first(headR, tailR,last_digit) == FAILURE)
                {
                    return FAILURE;
                }
            }
            else
            {
                // Remaining multiplication 
                if(dl_insert_first(headR1, tailR1,last_digit) == FAILURE)
                {
                    return FAILURE;
                }
            }

            temp1 = temp1->prev;
        }

        // Insert remaining carry
        if(carry != 0)
        {
            if(count == 0)
            {
                if(dl_insert_first(headR, tailR,carry) == FAILURE)
                {
                    return FAILURE;
                }
            }
            else
            {
                if(dl_insert_first(headR1,tailR1,carry) == FAILURE)
                {
                    return FAILURE;
                }
            }
        }

        if(count != 0)
        {
            // Add zeros at the tail 
            for(int i=0;i<count;i++)
            {
                if(dl_insert_last_for_list1(headR1, tailR1,0) == FAILURE)
                {
                    return FAILURE;
                }
            }

            // Add previous result and current partial product
            if(add(headR,tailR,headR1,tailR1,&backuphead,&backuptail) == FAILURE)
            {
                return FAILURE;
            }

            // Delete old result
            dl_delete_list(headR, tailR);

            // Delete partial product
            dl_delete_list(headR1, tailR1);

            // Store sum as the new result
            *headR = backuphead;
            *tailR = backuptail;

            backuphead = NULL;
            backuptail = NULL;
        }

        count++;
        temp2 = temp2->prev;
    }

    return SUCCESS;
}
int dl_delete_list(Dlist **head, Dlist **tail)
{
    if(*head==NULL)
    {
        return FAILURE;
    }
    Dlist*temp=(*head);
    
    while(temp!=NULL)
    {
        (*head)=temp->next;
        free(temp);
        temp=(*head);
    }
    *head=NULL;
    *tail=NULL;
    return SUCCESS;

}

//for division
int division(Dlist**head1,Dlist**tail1,Dlist**head2,Dlist**tail2,Dlist**headR1,Dlist**tailR1)
{
   if (*head2 == NULL)
        return FAILURE;

    // Division by zero check
    Dlist *temp2 = *head2;
    while (temp2 != NULL)
    {
        if (temp2->data != 0)
            break;
        temp2 = temp2->next;
    }

    if (temp2 == NULL)
    {
        printf("Division by zero error!!!");
        return FAILURE;
    }

    Dlist *remHead = NULL;
    Dlist *remTail = NULL;
    Dlist *temp = *head1;

    while (temp != NULL)
    {
        if(dl_insert_last_for_list1(&remHead, &remTail, temp->data)==FAILURE)
        {
            return FAILURE;
        }
        remove_leading_zeros(&remHead, &remTail);
        int q = 0;

        while (list_compare(&remHead, &remTail,head2, tail2) != list_2)
        {
            Dlist *subHead = NULL;
            Dlist *subTail = NULL;
            if(sub(&remHead, &remTail,head2, tail2, &subHead, &subTail)==FAILURE)
            {
                dl_delete_list(&remHead, &remTail);
                dl_delete_list(&subHead, &subTail);
                return FAILURE;
        
            }

            dl_delete_list(&remHead, &remTail);

            remHead = subHead;
            remTail = subTail;
            remove_leading_zeros(&remHead, &remTail);
            q++;
        }

        if(dl_insert_last_for_list1(headR1, tailR1,q)==FAILURE)
        {
            return FAILURE;
        }

        temp = temp->next;
    }

    // Remove leading zeros from quotient
    remove_leading_zeros(headR1, tailR1);
    dl_delete_list(&remHead, &remTail);

    return SUCCESS;

}
void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    while (*head != NULL &&
           (*head)->data == 0 &&
           (*head)->next != NULL)
    {
        Dlist *temp = *head;

        *head = temp->next;
        (*head)->prev = NULL;

        free(temp);
    }

    if (*head == NULL)
        *tail = NULL;
}