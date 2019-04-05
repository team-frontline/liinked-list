#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 1024
#define MAX_RANDOM 65535

int n = 0;
int m = 0;
int thread_count = 0;
float m_insert_frac = 0.0, m_delete_frac = 0.0, m_member_frac = 0.0;

// Total number of each operation
float m_insert = 0.0, m_delete = 0.0, m_member = 0.0;

struct node
{
   int val;
   struct node *next_node;
};

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

   //TODO: Validate Arguments

   //validate args
   if (m_member_frac + m_insert_frac + m_delete_frac != 1.0)
   {
      printf("Please give valid arguments!!");
      exit(0); //Successful failure
   }

   //Test
   printf("%d %d %d\n", n, m, thread_count);

   //Thread handlers initiating
   pthread_t *thread_handlers;
   thread_handlers = malloc(sizeof(pthread_t) * thread_count);
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
