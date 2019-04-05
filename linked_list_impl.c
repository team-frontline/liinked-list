#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX_THREADS 1024
#define MAX_RANDOM 65535

int n = 0;
int m = 0;
int thread_count = 0;
float m_insert_frac = 0.0, m_delete_frac = 0.0, m_member_frac = 0.0;

// Total number of each operation
float m_insert = 0.0, m_delete = 0.0, m_member = 0.0;

struct node *first_node;

struct node
{
   int val;
   struct node *next_node;
};

void gen_linked_list();

int Insert(int value, struct node **head_pp);

int Delete(int value, struct node **head_pp);

int Member(int value, struct node *first_node);

int main(int argc, char *argv[])
{
   //Setting input values
   n = (int)strtol(argv[1], (char **)NULL, 10);
   m = (int)strtol(argv[2], (char **)NULL, 10);
   thread_count = (int)strtol(argv[3], (char **)NULL, 10);

   // Setting the input values of operation fraction values
   m_member_frac = 0.2;
   m_insert_frac = 0.4;
   m_delete_frac = 0.4;

   // Calculating the total number od each operation
   m_insert = m_insert_frac * m;
   m_delete = m_delete_frac * m;
   m_member = m_member_frac * m;

   //TODO: Validate Arguments

   //validate args
   if (m_member_frac + m_insert_frac + m_delete_frac != 1.0)
   {
      printf("Please give valid arguments!!");
      exit(0); //Successful failure
   }

   //Test
   printf("%d %d %d\n", n, m, thread_count);

   pthread_mutex_t mutex;

   //Thread handlers initiating
   pthread_t *thread_handlers;
   thread_handlers = malloc(sizeof(pthread_t) * thread_count);

   // time variables
   struct timeval time_begin, time_end;

   // Initializing the mutex
   pthread_mutex_init(&mutex, NULL);

   // Getting the begin time stamp
   gettimeofday(&time_begin, NULL);

   // Getting the end time stamp
   gettimeofday(&time_end, NULL);

   // Destroying the mutex
   pthread_mutex_destroy(&mutex);

   printf("Linked List with a single mutex Time Spent : %.6f secs\n", CalcTime(time_begin, time_end));
   return 0;
}

//Check whether a given value is a member or not
int Member(int value, struct node *first_node)
{
   struct node *current_node = first_node;

   while (current_node != NULL && current_node->val < value)
   {
      current_node = current_node->next_node;
   }
   if (current_node->val = value)
   {
      return 1;
   }

   return 0;
}

void gen_linked_list()
{
   // Linked List Generation with Random values
   int i = 0;
   while (i < n)
   {
      if (Insert(rand() % 65535, &first_node) == 1)
         i++;
   }
}
