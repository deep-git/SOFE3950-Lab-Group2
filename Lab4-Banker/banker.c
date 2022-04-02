#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>

/* These may be any values >= 0 */
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3

// Declare mutex
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

// Initialize the call functions and methods
void *customer_threads(void *customer_res_num);
int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);
int checkSafe(int num);

/* ----------------------------------------- CHECK SAFE FUNCTION -------------------------------------- */

// checkSafe function to check if the system is safe or not
int checkSafe(int num) {
  // Variables for processing resources with num equal to the NUM_RESOURCES from parameter
  int process_resource[num];
  int finish_resource[num];

  // Fills the process_resource array with same values from available array
  for (int i = 0; i < NUM_RESOURCES; i++) {
    process_resource[num] = available[i];
  }

  // Sets the finish_resource of that resource num equal to -1 to indicate that the resource has not yet been
  // successfully finished
  finish_resource[num] = -1;

  // Nested loop to check if the system resource is safe or not
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      // If the finish_resource at that index is -1 and the value of need is less than or equal to
      // process_resource, then return -1 that the system is not safe
        if (finish_resource[i] == -1 && need[i][j] <= process_resource[i]) {
          return -1;

          // If the above condition is not met, then increment the process_resource element at that index with
          // the allocation value
        } else {
          process_resource[i] = process_resource[i] + allocation[i][j];
          finish_resource[i] = 0;     // Set finish_resource to 0 to indicate that resource is successfully finished
        }
    }
  }

  // Return 0 if the system is safe
  return 0;
}

/* -------------------------------------------- REQUEST RESOURCES ----------------------------------------- */

// Customer shared thread function for the request of resources
int request_resources(int customer_num, int request[]) {
  int safe = 0;

  // Loop to increment through the resources
  for (int i = 0; i < NUM_RESOURCES; i++) {
    // If the request is greater than need, return -1
    if (request[i] > need[customer_num][i]) {
      return -1;
      // If the request is greater than available, return -1
    } else if (request[i] > available[i]) {
        return -1;
    } else {

          safe = checkSafe(customer_num);     // Call checkSafe method and assign value of -1 or 0 to safe variable

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

          // If safe equals 0, the request is granted and return 0
          if (safe == 0) {
            printf("\nThe request is granted.\n");

            return 0;

            // If safe doesn't equal 0, the system is unsafe and return -1
          } else {
            pthread_mutex_lock(&mutex_available);     // Lock mutex
            // Critical section: increment available resources by the request value
            available[i] = available[i] + request[i];
            pthread_mutex_unlock(&mutex_available);     // Unlock mutex

            pthread_mutex_lock(&mutex_allocation);     // Lock mutex
            // Critical section: decrement resources allocated by the request value
            allocation[customer_num][i] = allocation[customer_num][i] - request[i];
            pthread_mutex_unlock(&mutex_allocation);     // Unlock mutex

            pthread_mutex_lock(&mutex_need);     // Lock mutex
            // Critical section: increment need by the request value
            need[customer_num][i] = need[customer_num][i] + request[i];     // Critical section
            pthread_mutex_unlock(&mutex_need);     // Unlock mutex

            printf("\nThe system is unsafe.\n");

            return -1;
          }
      }
    }
    return -1;
}

/* -------------------------------------------- RELEASE RESOURCES ----------------------------------------- */

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

  // Return 0
  return 0;
}

/* --------------------------------------- CUSTOMER ACCESS THREADS ------------------------------------ */

void *customer_threads(void *customer_res_num) {
  int num = (intptr_t)customer_res_num;     // Convert parameter to int and assign to num
  int request[NUM_RESOURCES];
  int request_check = 0;

  // Fills the request array with random numbers from 0 up to available[i] value
  for (int i = 0; i < NUM_RESOURCES; i++) {
    request[i] = rand() % available[i];
  }

  // If request_resources function returns -1, print request and deny resources
  if (request_resources(num, request) < 0) {
    request_check = 0;
    printf("Customer number %d and the resources are: ", num+1);

    for (int i = 0; i < NUM_RESOURCES; i++) {
      printf("%d ", request[i]);
    }

    printf("Denied resources.\n");

    // If request_resources function returns 0, print request and accept resources
  } else {
    request_check = 1;     // Set the request check to 1 for accepted resources
    printf("> Customer number %d and the resources are: ", num+1);

    for (int i = 0; i < NUM_RESOURCES; i++) {
      printf("%d ", request[i]);
    }

    printf("Accepted resources.\n");
  }

  // If the request check is equal to 1, meaning that the resource has been accepted
  if (request_check == 1) {
    int random_sleep = rand() % 5;
    sleep(random_sleep);     // Sleep for random time from 0 to 5 seconds
    release_resources(num, request);     // Calls the release_resources method
    printf("\n Customer number %d release some resources", num+1);     // Customer has release some resources
    printf("\n");
  }

  // Return 0
  return 0;
}

/* -------------------------------------------- MAIN FUNCTION  ----------------------------------------- */

int main(int argc, char *argv[]) {

  // Read in arguments, NUM_RESOURCES is the number of arguments
  // Place three resource values from user input into the available array
  if (argc == (NUM_RESOURCES + 1)) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
      available[i] = abs(atoi(argv[i+1]));
    }
    printf("\n");
  }

  srand(time(NULL));     // Declare random time

  // Nested loop to fill the maximum array with random numbers from 0 to the value of available[j]
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      maximum[i][j] = rand() % available[j];
      allocation[i][j] = 0;
    }
  }

  // Print the maximum array
  printf("Maximum matrix\n");
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      printf("%d ", maximum[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  // Print the need array
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

  // Initialize and create threads
  pthread_t tid_request_release;

  // Nested loop to create threads
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      // Create threads with value of j as argument
      pthread_create(&tid_request_release, NULL, customer_threads, (void *) (intptr_t)j);
    }
  }

  // Sleep to wait for thread joining
  sleep(1);

  // Return exit success
  return EXIT_SUCCESS;
}
