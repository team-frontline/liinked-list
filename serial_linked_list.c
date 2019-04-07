#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "statistic.h"

#define MAX_RANDOM 65535

int number_of_times = 25;

int n = 0;
int m = 0;
float inset_percentage, delete_percentage, member_percentage;
double time_taken = 0;

struct linked_list_node
{
    int value;
    struct linked_list_node *next_node;
};

double serial_linked_list();

int Insert(int value, struct linked_list_node **list_head);

int Delete(int value, struct linked_list_node **list_head);

int Member(int value, struct linked_list_node *list_head);

void getInputs(int argc, char const *argv[]);

double CalculateTime(struct timeval time_begin, struct timeval time_end);

int main(int argc, char const *argv[])
{
    getInputs(argc, argv);
    double times_array[number_of_times];
    int k = 0;
    while (k < number_of_times)
    {
        time_taken = serial_linked_list();
        times_array[k] = time_taken;
        k++;
    }

    printf("Mean execution time for %i number of exectuions: %f", number_of_times, calculate_mean(times_array, number_of_times));
    printf("\nStandard deviation for %i number of exectuions: %f", number_of_times, calculate_std(times_array, number_of_times));
    printf("\nSample size for accuracy of ±5 and 95 confidence level: %f", sample_size(times_array, number_of_times, 1.96, 5));

    return 0;
}

double serial_linked_list()
{
    struct linked_list_node *head = NULL;
    struct timeval time_begin, time_end;

    int i = 0;
    while (i < n)
    {
        i = i + Insert(rand() % MAX_RANDOM, &head);
    }

    int count_total = 0;
    int count_member = 0;
    int count_insert = 0;
    int count_delete = 0;

    float target_insert = inset_percentage * m;
    float target_delete = delete_percentage * m;
    float target_member = member_percentage * m;

    gettimeofday(&time_begin, NULL);

    while (count_total < m)
    {
        int random_value = rand() % MAX_RANDOM;
        int random_operation_selection = rand() % 3;

        if (random_operation_selection == 0 && count_insert < target_insert)
        {
            Insert(random_value, &head);
            count_insert++;
        }

        if (random_operation_selection == 1 && count_delete < target_delete)
        {
            Delete(random_value, &head);
            count_delete++;
        }

        if (random_operation_selection == 2 && count_member < target_member)
        {
            Member(random_value, head);
            count_member++;
        }
        count_total = count_insert + count_delete + count_member;
    }
    gettimeofday(&time_end, NULL);
    printf("Serial Linked List Time Spent : %.6f secs\n", CalculateTime(time_begin, time_end));
    free(head);

    return CalculateTime(time_begin, time_end);
}

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

void getInputs(int argc, char const *argv[])
{
    n = (int)strtol(argv[1], (char **)NULL, 10);
    m = (int)strtol(argv[2], (char **)NULL, 10);

    inset_percentage = (float)atof(argv[3]);
    delete_percentage = (float)atof(argv[4]);
    member_percentage = (float)atof(argv[5]);
}

double CalculateTime(struct timeval time_begin, struct timeval time_end)
{
    return (double)(time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double)(time_end.tv_sec - time_begin.tv_sec);
}
