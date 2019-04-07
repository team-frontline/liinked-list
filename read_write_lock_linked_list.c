#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX_THREADS 1024
#define MAX_RANDOM 65535

int n = 0, m = 0, thread_count = 0;

float m_insert_frac = 0.0, m_delete_frac = 0.0, m_member_frac = 0.0;

int m_insert = 0, m_delete = 0, m_member = 0;

struct node *head = NULL;
pthread_rwlock_t rwlock;

//Node definition
struct node
{
    int data;
    struct node *next_node;
};

int Insert(int value, struct node **head_pp);

int Delete(int value, struct node **head_pp);

int Member(int value, struct node *head_p);

void getInput(int argc, char *argv[]);

double CalcTime(struct timeval time_begin, struct timeval time_end);

void *Thread_Operation(void *id);

int main(int argc, char *argv[])
{

    //Setting input values
    n = (int)strtol(argv[1], (char **)NULL, 10);
    m = (int)strtol(argv[2], (char **)NULL, 10);
    thread_count = (int)strtol(argv[3], (char **)NULL, 10);

    // Setting the input values of operation fraction values
    m_member_frac = (float)atof(argv[4]);
    m_insert_frac = (float)atof(argv[5]);
    m_delete_frac = (float)atof(argv[6]);

    // Calculating the total number od each operation
    m_insert = (int)(m_insert_frac * m);
    m_delete = (int)(m_delete_frac * m);
    m_member = (int)(m_member_frac * m);

    //TODO: Validate Arguments

    //validate args
    if (m_member_frac + m_insert_frac + m_delete_frac != 1.0)
    {
        printf("Please give valid arguments!!");
        exit(0); //Successful failure
    }

    //Test
    printf("n=%d, m=%d thread_count=%d \n", n, m, thread_count);

    pthread_t *thread_handlers;
    thread_handlers = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);

    // time variables
    struct timeval time_begin, time_end;

    int *thread_id;
    thread_id = (int *)malloc(sizeof(int) * thread_count);

    // Linked List Generation with Random values
    int i = 0;
    while (i < n)
    {
        if (Insert(rand() % 65535, &head) == 1)
            i++;
    }

    pthread_rwlock_init(&rwlock, NULL);
    gettimeofday(&time_begin, NULL);

    // Thread Creation
    i = 0;
    while (i < thread_count)
    {
        thread_id[i] = i;
        pthread_create(&thread_handlers[i], NULL, (void *)Thread_Operation, (void *)&thread_id[i]);
        i++;
    }

    // Thread Join
    i = 0;
    while (i < thread_count)
    {
        pthread_join(thread_handlers[i], NULL);
        i++;
    }
    gettimeofday(&time_end, NULL);
    pthread_rwlock_destroy(&rwlock);

    printf("Linked List with read write locks Time Spent : %.6f\n", CalcTime(time_begin, time_end));

    return 0;
}

// Linked List Membership function
int Member(int value, struct node *head_p)
{
    struct node *current_p = head_p;

    while (current_p != NULL && current_p->data < value)
        current_p = current_p->next_node;

    if (current_p == NULL || current_p->data > value)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Linked List Insertion function
int Insert(int value, struct node **head_pp)
{
    struct node *curr_p = *head_pp;
    struct node *pred_p = NULL;
    struct node *temp_p = NULL;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next_node;
    }

    if (curr_p == NULL || curr_p->data > value)
    {
        temp_p = malloc(sizeof(struct node));
        temp_p->data = value;
        temp_p->next_node = curr_p;

        if (pred_p == NULL)
            *head_pp = temp_p;
        else
            pred_p->next_node = temp_p;

        return 1;
    }
    else
        return 0;
}

// Linked List Deletion function
int Delete(int value, struct node **head_pp)
{
    struct node *curr_p = *head_pp;
    struct node *pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next_node;
    }

    if (curr_p != NULL && curr_p->data == value)
    {
        if (pred_p == NULL)
        {
            *head_pp = curr_p->next_node;
            free(curr_p);
        }
        else
        {
            pred_p->next_node = curr_p->next_node;
            free(curr_p);
        }

        return 1;
    }
    else
        return 0;
}

// Thread Operations
void *Thread_Operation(void *thread_id)
{

    int local_m = 0;
    int local_m_insert = 0;
    int local_m_delete = 0;
    int local_m_member = 0;

    int id = *(int *)thread_id;

    // Generate local no of insertion operations without loss
    if (m_insert % thread_count == 0 || m_insert % thread_count <= id)
    {
        local_m_insert = m_insert / thread_count;
    }
    else if (m_insert % thread_count > id)
    {
        local_m_insert = m_insert / thread_count + 1;
    }

    // Generate local no of member operations without loss
    if (m_member % thread_count == 0 || m_member % thread_count <= id)
    {
        local_m_member = m_member / thread_count;
    }
    else if (m_member % thread_count > id)
    {
        local_m_member = m_member / thread_count + 1;
    }

    // Generate local no of deletion operations without loss
    if (m_delete % thread_count == 0 || m_delete % thread_count <= id)
    {
        local_m_delete = m_delete / thread_count;
    }
    else if (m_delete % thread_count > id)
    {
        local_m_delete = m_delete / thread_count + 1;
    }

    local_m = local_m_insert + local_m_delete + local_m_member;

    int count_tot = 0;
    int count_member = 0;
    int count_insert = 0;
    int count_delete = 0;

    int finished_member = 0;
    int finished_insert = 0;
    int delete_finished = 0;

    int i = 0;
    while (count_tot < local_m)
    {

        int random_value = rand() % MAX_RANDOM;
        int random_select = rand() % 3;

        // Member operation
        if (random_select == 0 && finished_member == 0)
        {
            if (count_member < local_m_member)
            {
                pthread_rwlock_rdlock(&rwlock);
                Member(random_value, head);
                pthread_rwlock_unlock(&rwlock);
                count_member++;
            }
            else
                finished_member = 1;
        }

        // Insert Operation
        else if (random_select == 1 && finished_insert == 0)
        {
            if (count_insert < local_m_insert)
            {
                pthread_rwlock_wrlock(&rwlock);
                Insert(random_value, &head);
                pthread_rwlock_unlock(&rwlock);
                count_insert++;
            }
            else
                finished_insert = 1;
        }

        // Delete Operation
        else if (random_select == 2 && delete_finished == 0)
        {

            if (count_delete < local_m_delete)
            {
                pthread_rwlock_wrlock(&rwlock);
                Delete(random_value, &head);
                pthread_rwlock_unlock(&rwlock);
                count_delete++;
            }
            else
                delete_finished = 1;
        }
        count_tot = count_insert + count_member + count_delete;
        i++;
    }
    return NULL;
}

// Calculating time
double CalcTime(struct timeval time_begin, struct timeval time_end)
{
    return (double)(time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double)(time_end.tv_sec - time_begin.tv_sec);
}
