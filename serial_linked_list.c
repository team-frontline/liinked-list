#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_RANDOM 65535

int n = 0;
int m = 0;
float inset_percentage, delete_percentage, member_percentage;

struct linked_list_node
{
    int value;
    struct linked_list_node *next_node;
};

int Insert(int value, struct linked_list_node **list_head);

int Delete(int value, struct linked_list_node **list_head);

int Member(int value, struct linked_list_node **list_head);

int Insert(int value, struct linked_list_node **list_head)
{
    
}
