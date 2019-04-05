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

int Member(int value, struct linked_list_node *list_head);

int Insert(int value, struct linked_list_node **list_head)
{
    struct linked_list_node *current_pointer = *list_head;
    struct linked_list_node *predece_pointer = NULL;
    struct linked_list_node *temp_pointer = NULL;

    while (current_pointer != NULL && current_pointer->value < value)
    {
        predece_pointer = current_pointer;
        current_pointer = current_pointer->next_node;
    }

    if (current_pointer == NULL || current_pointer->value > value)
    {
        temp_pointer = malloc(sizeof(struct linked_list_node));
        temp_pointer->value = value;
        temp_pointer->next_node = current_pointer;

        if (predece_pointer == NULL)
        {
            *list_head = temp_pointer;
        }
        else
        {
            predece_pointer->next_node = temp_pointer;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int Delete(int value, struct linked_list_node **list_head)
{
    struct linked_list_node *current_pointer = *list_head;
    struct linked_list_node *predece_pointer = NULL;

    while (current_pointer != NULL && current_pointer->value < value)
    {
        predece_pointer = current_pointer;
        current_pointer = current_pointer->next_node;
    }

    if (current_pointer != NULL && current_pointer->value == value)
    {
        if (predece_pointer == NULL)
        {
            *list_head = current_pointer->next_node;
            free(current_pointer);
        }

        else
        {
            predece_pointer->next_node = current_pointer->next_node;
            free(current_pointer);
        }
    }
    return 0;
}

int Member(int value, struct linked_list_node *list_head)
{
    struct linked_list_node *current_pointer = list_head;

    while (current_pointer != NULL && current_pointer->value < value)
    {
        current_pointer = current_pointer->next_node;

        if (current_pointer->value == value)
        {
            return 1;
        }
    }
    return 0;
}
