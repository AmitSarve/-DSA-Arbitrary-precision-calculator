#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

#define SUCCESS 0
#define FAILURE -1
#define list_1 1
#define list_2 0
#define equal_list 2

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;


int dl_insert_last_for_list1(Dlist**head, Dlist**tail, int data);
int validate_ip(char*[],int);
void print_list(Dlist*head );
void print_result(Dlist *head, int negative);
int add(Dlist** ,Dlist** ,Dlist** , Dlist** ,Dlist** ,Dlist** );
int sub(Dlist** ,Dlist** ,Dlist** , Dlist** ,Dlist** ,Dlist** );
int list_compare(Dlist** ,Dlist**,Dlist**,Dlist**);
int dl_insert_first(Dlist **head, Dlist **tail, int data);
int mult(Dlist**,Dlist**,Dlist**,Dlist**,Dlist**,Dlist**,Dlist**,Dlist** );
int dl_delete_list(Dlist **, Dlist **);
void remove_leading_zeros(Dlist **, Dlist **);
int division(Dlist**,Dlist**,Dlist**,Dlist**,Dlist**,Dlist**);
#endif