#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define COUNT 9     //num or row/column/grid
#define TOTAL 45    //sum of numbers

// Structure for containing the row and columns
typedef struct grid {
    int row;
    int column;
} parameters;

// Initialize the functions
void * count_rows(void * data);
void * count_columns(void * data);
void * validate_number(void * data);

// Declare the sudoku board array
int grid_numbers[9][9];

// Declare and initialize the array for checking valid board solution
int valid[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main (int argc, char **argv) {
  (void)argc; // disregard argc
  FILE *file; // Declaring a file pointer

  //Prompt user how to initiate program
  if(argc < 2){
    printf("--------------------------------------\n");
    printf("USAGE: ./sudoku-validator.o <filename>\n");
    printf("--------------------------------------\n");
    exit(0);
  }

  // file = fopen("puzzle.txt", "r"); // Opening the file with read permissions
  file = fopen(argv[1], "r"); // Opening the file (argument) with read permission

  printf("\nSudoku Solution Validator");

  // If the file opens, read the board inputs into the grid_numbers array
  if (file != NULL) {
    for (int i = 0; i < 9; i++) {
      printf("\n    ");
      for (int j = 0; j < 9; j++) {
        // Stores the board numbers from the file in the array
          fscanf(file, "%d", &grid_numbers[i][j]);

          // Prints the board
          printf("%d ", grid_numbers[i][j]);
      }
    }

    // If the file does not open, show error message
  } else {
    printf("Error opening the file.\n");
  }

// Close the file
fclose(file);

printf("\n");

    // Create parameters for each data pointer and thread (11 threads)
    parameters *data0 = (parameters *) malloc(sizeof(parameters));
    data0->row = 0; data0->column = 0;

    // Grid parameters
    parameters *data1 = (parameters *) malloc(sizeof(parameters));
    data1->row = 0; data1->column = 0;
    parameters *data2 = (parameters *) malloc(sizeof(parameters));
    data2->row = 0; data2->column = 3;
    parameters *data3 = (parameters *) malloc(sizeof(parameters));
    data3->row = 0; data3->column = 6;
    parameters *data4 = (parameters *) malloc(sizeof(parameters));
    data4->row = 3; data4->column = 0;
    parameters *data5 = (parameters *) malloc(sizeof(parameters));
    data5->row = 3; data5->column = 3;
    parameters *data6 = (parameters *) malloc(sizeof(parameters));
    data6->row = 3; data6->column = 6;
    parameters *data7 = (parameters *) malloc(sizeof(parameters));
    data7->row = 6; data7->column = 0;
    parameters *data8 = (parameters *) malloc(sizeof(parameters));
    data8->row = 6; data8->column = 3;
    parameters *data9 = (parameters *) malloc(sizeof(parameters));
    data9->row = 6; data9->column = 6;

    // Initialize the threads
    pthread_t t_row, t_col, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9;

    // Create the threads
    pthread_create(&t_row, NULL, count_rows, data0);
    pthread_create(&t_col, NULL, count_columns, data0);
    pthread_create(&t_1, NULL, validate_number, data2);
    pthread_create(&t_2, NULL, validate_number, data2);
    pthread_create(&t_3, NULL, validate_number, data3);
    pthread_create(&t_4, NULL, validate_number, data4);
    pthread_create(&t_5, NULL, validate_number, data5);
    pthread_create(&t_6, NULL, validate_number, data6);
    pthread_create(&t_7, NULL, validate_number, data7);
    pthread_create(&t_8, NULL, validate_number, data8);
    pthread_create(&t_9, NULL, validate_number, data9);

    // Initialize variables to store the thread results after thread joining
    void * rows;
    void * columns;
    void * grid1;
    void * grid2;
    void * grid3;
    void * grid4;
    void * grid5;
    void * grid6;
    void * grid7;
    void * grid8;
    void * grid9;

    // Join the threads
    pthread_join(t_row, &rows);
    pthread_join(t_col, &columns);
    pthread_join(t_1, &grid1);
    pthread_join(t_2, &grid2);
    pthread_join(t_3, &grid3);
    pthread_join(t_4, &grid4);
    pthread_join(t_5, &grid5);
    pthread_join(t_6, &grid6);
    pthread_join(t_7, &grid7);
    pthread_join(t_8, &grid8);
    pthread_join(t_9, &grid9);

    printf("\n");

    //testing - print valid array
    printf("VALIDITY TRACKER\n1st num = [rows], 2nd num = [columns], rest = [grid]\n");
    for (int i = 0; i < 11; i++) {
      printf("%d ", valid[i]);
    }

    printf("\n");

    //Prompt user if given puzzle is valid or not
    for (int i = 0; i < 11; i++) {
      // If not valid, print that the puzzle is not solved correctly
      if (valid[i] == 0) {
        printf("\nThe sudoku puzzle is NOT SOLVED correctly, please try again\n\n");
        return 0;
      }
    }

    // If valid, print that the puzzle was solved successfully
    printf("\nThe sudoku puzzle was SOLVED successfully, congratulations!\n\n");
    return 0;
}

// Checks whether or not the rows contain numbers 1-9, if they do, then return 1
void * count_rows(void * data) {

  // Creates parameter entry equal to the argument
  parameters *data_entry = (parameters *) data;
  // Sets the count_rows and count_columns variables equal to the row and column number of that entry
  int count_rows = data_entry->row;
  int count_columns = data_entry->column;

  // Initial valid row entry is 0
  int valid_row[COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Nested loop to go through the board and check if the rows contain numbers 1-9
  for (int i = count_rows; i < COUNT; i++) {

    for (int j = count_columns; j < COUNT; j++) {

      // Declares and initializes the num_valid variable equal to the number at the specified grid location
      int num_valid = grid_numbers[i][j];

      // If invalid or double number exists, exit the thread
      if (num_valid < 0 || num_valid > 9 || valid_row[num_valid - 1] == 1) {
        pthread_exit(NULL);

      } else {
        // Sets the valid_row array of entry num_valid equal to 1 to show that row is valid
        valid_row[num_valid - 1] = 1;

      }

    }

    // Change the valid to 1 to show that the row is valid
    valid[0] = 1;
  }

  // Exits the thread
  pthread_exit(NULL);
}

// Checks whether or not the columns contain numbers 1-9, if they do, then return 1
void * count_columns(void * data) {

  parameters *data_entry = (parameters *) data;
  int count_rows = data_entry->row;
  int count_columns = data_entry->column;
  // Initial valid column entry is 0
  int valid_columns[COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Nested loop to go through the board and check if the columns contain numbers 1-9
  for (int i = count_columns; i < COUNT; i++) {

    for (int j = count_rows; j < COUNT; j++) {

      int num_valid = grid_numbers[j][i];


      if (num_valid < 0 || num_valid > 9 || valid_columns[num_valid - 1] == 1) {
        pthread_exit(NULL);

      } else {
        valid_columns[num_valid - 1] = 1;
      }

    }
    // Change the valid to 1 to show that the column is valid
    valid[1] = 1;
  }

  pthread_exit(NULL);
}

// Checks whether or not each of the 9 grids contain numbers 1-9, if they do, then return 1
void * validate_number(void * data) {

  parameters *data_entry = (parameters *) data;
  int count_rows = data_entry->row;
  int count_columns = data_entry->column;
  // Initial valid grid entry is 0
  int valid_grid[COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Nested loop to go through the board and check if the grids contain numbers 1-9
  for (int i = count_rows; i < COUNT; i++) {

    for (int j = count_columns; j < COUNT; j++) {

      int num_valid = grid_numbers[i][j];

      if (num_valid < 0 || num_valid > 9 || valid_grid[num_valid - 1] == 1) {
        pthread_exit(NULL);

      } else {
        valid_grid[num_valid - 1] = 1;
      }

    }
  }

  // Change the valid to 1 to show that all the 3x3 grids are valid
  for (int i = 2; i < COUNT+2; i++) {
      valid[i] = 1;
  }

  pthread_exit(NULL);
}
