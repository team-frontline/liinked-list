#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX_THREADS 1024
#define MAX_RANDOM 65535
#define NO_OF_OPS 3

int n = 0;
int m = 0;
int thread_count = 0;
float m_insert_frac = 0.0, m_delete_frac = 0.0, m_member_frac = 0.0;

// Total number of each operation
float m_insert = 0.0, m_delete = 0.0, m_member = 0.0;

//declare counts
int count_member_op, count_insert_op, count_delete_op;

struct node *first_node;

struct node
{
   int val;
   struct node *next_node;
};

pthread_mutex_t mutex;

void gen_linked_list();

void print_linked_list(struct node *first_node_p);

int Insert(int value, struct node **first_node_pp);

int Delete(int value, struct node **first_node_pp);

int Member(int value, struct node *first_node_p);

double calc_time(struct timeval time_begin, struct timeval time_end);

void *thread_ops();

int main(int argc, char *argv[])
{
   //Setting input values
   n = (int)strtol(argv[1], (char **)NULL, 10);
   m = (int)strtol(argv[2], (char **)NULL, 10);
   thread_count = (int)strtol(argv[3], (char **)NULL, 10);

   // Setting the input values of operation fraction values
   m_member_frac = (float) atof(argv[4]);;
   m_insert_frac = (float) atof(argv[5]);;
   m_delete_frac = (float) atof(argv[6]);;

   // Calculating the total number od each operation
   m_insert = m_insert_frac * m;
   m_delete = m_delete_frac * m;
   m_member = m_member_frac * m;

   //Counts init
   count_member_op = 0, count_insert_op = 0, count_delete_op = 0;

   //TODO: Validate Arguments

   //validate args
   if (m_member_frac + m_insert_frac + m_delete_frac != 1.0)
   {
      printf("Please give valid arguments!!");
      exit(0); //Successful failure
   }

   //Test
   printf("n=%d, m=%d thread_count=%d \n", n, m, thread_count);

   //Thread handlers initiating
   pthread_t *thread_handlers;
   thread_handlers = malloc(sizeof(pthread_t) * thread_count);

   // time variables
   struct timeval time_begin, time_end;

   gen_linked_list();
   print_linked_list(first_node);

   // Initializing the mutex
   pthread_mutex_init(&mutex, NULL);

   // Getting the begin time stamp
   gettimeofday(&time_begin, NULL);

   /*
   *  Thread Creation
   *  Thread Join
   */
   int i = 0;
   while (i < thread_count)
   {
      pthread_create(&thread_handlers[i], NULL, (void *)thread_ops, NULL);
      i++;
   }

   int j = 0;
   while (j < thread_count)
   {
      pthread_join(thread_handlers[j], NULL);
      j++;
   }

   // Getting the end time stamp
   gettimeofday(&time_end, NULL);

   // Destroying the mutex
   pthread_mutex_destroy(&mutex);

   print_linked_list(first_node);
   printf("\nLinked List with a single mutex Time Spent : %.6f secs\n", calc_time(time_begin, time_end));
   return 0;
}

//Check whether a given value is a member or not
int Member(int value, struct node *first_node_p)
{
   struct node *current_node = first_node_p;

   while (current_node != NULL && current_node->val < value)
   {
      current_node = current_node->next_node;
   }
   if (current_node->val == value)
   {
      return 1;
   }

   return 0;
}

//Insert a value to the linked-list
int Insert(int value, struct node **first_node_pp)
{
   struct node *current_node = *first_node_pp;
   struct node *prev_node = NULL;
   struct node *temp_node = NULL;

   while (current_node != NULL && current_node->val < value)
   {
      prev_node = current_node;
      current_node = current_node->next_node;
   }
   if (current_node == NULL || current_node->val > value)
   {
      temp_node = malloc(sizeof(struct node));
      temp_node->val = value;
      temp_node->next_node = current_node;

      if (prev_node != NULL)
      {
         prev_node->next_node = temp_node;
      }
      else
      {
         *first_node_pp = temp_node;
      }
      return 1;
   }
   return 0;
}

//Delete a node in the linkedlist
int Delete(int value, struct node **first_node_pp)
{
   struct node *current_node = *first_node_pp;
   struct node *prev_node = NULL;

   while (current_node != NULL && current_node->val < value)
   {
      prev_node = current_node;
      current_node = current_node->next_node;
   }
   if (current_node->val == value)
   {
      if (prev_node != NULL)
      {
         prev_node->next_node = current_node->next_node;
      }
      else
      {
         *first_node_pp = current_node->next_node;
      }
      free(current_node);
      return 1;
   }
   return 0;
}

//Generate the linked-list
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

//print linked_list
void print_linked_list(struct node *first_node_p)
{
   printf("----\n\n");
   struct node *current_node = first_node_p;

   while (current_node != NULL)
   {
      printf(" %d,", current_node->val);
      current_node = current_node->next_node;
   }
   printf("\n");
}

// Calculating time
double calc_time(struct timeval time_begin, struct timeval time_end)
{
   return (double)(time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double)(time_end.tv_sec - time_begin.tv_sec);
}

void *thread_op(int id)
{
   printf("  -thread running..\n");
}

// Thread Operations
void *thread_ops()
{
   while (count_delete_op + count_insert_op + count_member_op < m)
   {
      printf("  -thread vls:(%d,%d,%d) of (%f,%f,%f)",
             count_delete_op, count_insert_op, count_member_op, m_delete, m_insert, m_member);

      int value = rand() % MAX_RANDOM;
      int rn = rand();
      int random_op_no = rn % 3;
      // int random_op_no = 2;

      printf("  %d,%d,%d\n", value, random_op_no, rn);
      switch (random_op_no)
      {
      case 0:
         /* Member Operation*/
         if (count_member_op < m_member)
         {
            pthread_mutex_lock(&mutex);
            Member(value, first_node);
            count_member_op++;
            pthread_mutex_unlock(&mutex);
         }
         break;

      case 1:
         /* Insert Operation */
         if (count_insert_op < m_insert)
         {
            pthread_mutex_lock(&mutex);
            Insert(value, &first_node);
            count_insert_op++;
            pthread_mutex_unlock(&mutex);
         }
         break;

      case 2:
         if (count_delete_op < m_delete)
         {
            pthread_mutex_lock(&mutex);
            Delete(value, &first_node);
            count_delete_op++;
            pthread_mutex_unlock(&mutex);
         }
         break;

      default:
         break;
      }
   }
}