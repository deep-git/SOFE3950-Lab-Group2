#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>

/* These may be any values >= 0 */
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3

// Declare mutex
pthread_mutex_t mutex;
pthread_mutex_t mutex_available;
pthread_mutex_t mutex_allocation;
pthread_mutex_t mutex_need;

/* The available amount of each resource */
int available[NUM_RESOURCES];

/* The maximum demand of each customer */
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

/* The amount currently allocated to each customer */
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

/* The remaining need of each customer */
int need[NUM_CUSTOMERS][NUM_RESOURCES];

int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);

// Generate matrix with random numbers up to available[j]
void generate_matrix() {
  srand(time(NULL));

  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      maximum[i][j] = rand() % available[j];
      allocation[i][j] = 0;
    }
  }

}

// Customer shared thread function for the request of resources
int request_resources(int customer_num, int request[]) {

  // Loop to check through each resource
  for (int i = 0; i < NUM_RESOURCES; i++) {

    pthread_mutex_lock(&mutex_available);     // Lock mutex
    // Critical section: decrement available resources by the request value
    available[i] = available[i] - request[i];
    pthread_mutex_unlock(&mutex_available);     // Unlock mutex

    pthread_mutex_lock(&mutex_allocation);     // Lock mutex
    // Critical section: increment resources allocated by the request value
    allocation[customer_num][i] = allocation[customer_num][i] + request[i];
    pthread_mutex_unlock(&mutex_allocation);     // Unlock mutex

    pthread_mutex_lock(&mutex_need);     // Lock mutex
    // Critical section: decrement need by the request value
    need[customer_num][i] = need[customer_num][i] - request[i];     // Critical section
    pthread_mutex_unlock(&mutex_need);     // Unlock mutex

  }

  // If check safe returns -1, undo the above incrementations/decrementations by doing the opposite

  return 0;
}

// Customer shared thread function for the release of resources
int release_resources(int customer_num, int release[]) {

  // Loop to check through each resource
  for (int i = 0; i < NUM_RESOURCES; i++) {

    pthread_mutex_lock(&mutex_available);     // Lock mutex
    // Critical section: increment available according to release value
    available[i] = available[i] + release[i];
    pthread_mutex_unlock(&mutex_available);     // Unlock mutex

    pthread_mutex_lock(&mutex_allocation);     // Lock mutex
    // Critical section: decrement resource allocation by the release value
    allocation[customer_num][i] = allocation[customer_num][i] - release[i];
    pthread_mutex_unlock(&mutex_allocation);     // Unlock mutex

    pthread_mutex_lock(&mutex_need);     // Lock mutex
    // Critical section: increment need by the amount of resources allocated
    need[customer_num][i] = maximum[customer_num][i] + allocation[customer_num][i];     // Critical section
    pthread_mutex_unlock(&mutex_need);     // Unlock mutex

  }

  return 0;
}

int main(int argc, char *argv[]) {

  pthread_mutex_init(&mutex, NULL);     // Initialize mutex

  // Read in arguments, NUM_RESOURCES is the number of arguments
  // Place three resource values from user input into the available array
  if (argc == (NUM_RESOURCES + 1)) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
      available[i] = abs(atoi(argv[i+1]));
    }
    printf("\n");
  }

  // Allocate the resources
  // Call to generate the matrix
  generate_matrix();

  // Print the maximum array matrix
  printf("Maximum matrix\n");
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      printf("%d ", maximum[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  // Print the need array matrix
  printf("Need maxtrix\n");
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      // Calculate the need array values by subtracting resource allocation from the maximum amount
      need[i][j] = maximum[i][j] - allocation[i][j];
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  // Print the allocation matrix
  printf("Allocation matrix\n");
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      printf("%d ", allocation[i][j]);
    }
    printf("\n");
  }

  // Initialize and create threads


  pthread_mutex_destroy(&mutex);     // Destroy mutex

  return EXIT_SUCCESS;
}
