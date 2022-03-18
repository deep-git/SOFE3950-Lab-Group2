#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define COUNT 9

typedef struct grid {
    int row;
    int column;
} parameters;

/*
static int sudoku_board[9][9] = {
                                {5, 3, 0, 0, 7, 0, 0, 0, 0},
                                {6, 0, 0, 1, 9, 5, 0, 0, 0},
                                {0, 9, 8, 0, 0, 0, 0, 6, 0},
                                {8, 0, 0, 0, 6, 0, 0, 0, 3},
                                {4, 0, 0, 8, 0, 3, 0, 0, 1},
                                {7, 0, 0, 0, 2, 0, 0, 0, 6},
                                {0, 6, 0, 0, 0, 0, 2, 8, 0},
                                {0, 0, 0, 4, 1, 9, 0, 0, 5},
                                {0, 0, 0, 0, 8, 0, 0, 7, 9}
                            };
*/

void * count_rows(void * data);
void * count_columns(void * data);
void * validate_number(void * data);

int grid_numbers[9][9];
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

  if (file != NULL) {
    for (int i = 0; i < 9; i++) {
      printf("\n    ");
      for (int j = 0; j < 9; j++) {
          fscanf(file, "%d", &grid_numbers[i][j]);
          printf("%d ", grid_numbers[i][j]);
      }
    }
  } else {
    printf("Error opening the file.\n");
  }

fclose(file);

printf("\n");

    // Create parameters for each data pointer and thread (11 threads)
    parameters *data0 = (parameters *) malloc(sizeof(parameters));
    data0->row = 0;
    data0->column = 0;

    parameters *data1 = (parameters *) malloc(sizeof(parameters));
    data1->row = 0;
    data1->column = 0;

    parameters *data2 = (parameters *) malloc(sizeof(parameters));
    data2->row = 0;
    data2->column = 3;

    parameters *data3 = (parameters *) malloc(sizeof(parameters));
    data3->row = 0;
    data3->column = 6;

    parameters *data4 = (parameters *) malloc(sizeof(parameters));
    data4->row = 3;
    data4->column = 0;

    parameters *data5 = (parameters *) malloc(sizeof(parameters));
    data5->row = 3;
    data5->column = 3;

    parameters *data6 = (parameters *) malloc(sizeof(parameters));
    data6->row = 3;
    data6->column = 6;

    parameters *data7 = (parameters *) malloc(sizeof(parameters));
    data7->row = 6;
    data7->column = 0;

    parameters *data8 = (parameters *) malloc(sizeof(parameters));
    data8->row = 6;
    data8->column = 3;

    parameters *data9 = (parameters *) malloc(sizeof(parameters));
    data9->row = 6;
    data9->column = 6;

    // Create threads
    pthread_t t_row, t_col, t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9;

    pthread_create(&t_row, NULL, count_rows, data0);
    pthread_create(&t_col, NULL, count_columns, data0);
    pthread_create(&t_1, NULL, validate_number, data1);
    pthread_create(&t_2, NULL, validate_number, data2);
    pthread_create(&t_3, NULL, validate_number, data3);
    pthread_create(&t_4, NULL, validate_number, data4);
    pthread_create(&t_5, NULL, validate_number, data5);
    pthread_create(&t_6, NULL, validate_number, data6);
    pthread_create(&t_7, NULL, validate_number, data7);
    pthread_create(&t_8, NULL, validate_number, data8);
    pthread_create(&t_9, NULL, validate_number, data9);

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

    /*
    if ((int) rows == 1 && (int) columns == 1 && (int) grid1 == 1 && (int) grid2 == 1 && (int) grid3 == 1 && (int) grid4 == 1 && (int) grid5 == 1 && (int) grid6 == 1 &&
    (int) grid7 == 1 && (int) grid8 == 1 && (int) grid9 == 1) {
        printf("The sudoku puzzle was solved successfully, congratulations!\n");
    } else {
        printf("The sudoku puzzle is not solved correctly, please try again\n");
    }
    */

    printf("\n");

    //testing - print valid array
    printf("VALIDITY TRACKER\n1st num = [rows], 2nd num = [columns], rest = [grid]\n");
    for (int i = 0; i < 11; i++) {     
      printf("%d ", valid[i]);
    }

    printf("\n");

    //Prompt user if given puzzle is valid or not
    for (int i = 0; i < 11; i++) {
      if (valid[i] == 0) {
        printf("\nThe sudoku puzzle is NOT SOLVED correctly, please try again\n\n");
        return 0;
      }
    }

    printf("\nThe sudoku puzzle was SOVLED successfully, congratulations!\n\n");
    return 0;
}

// Checks whether or not the rows contain numbers 1-9, if they do, then return 1
void * count_rows(void * data) {

  parameters *data_entry = (parameters *) data;
  int count_rows = data_entry->row;
  int count_columns = data_entry->column;
  int valid_row[COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = count_rows; i < COUNT; i++) {

    for (int j = count_columns; j < COUNT; i++) {

      int num_valid = grid_numbers[i][j];

      if (num_valid < 0 || num_valid > 9 || valid_row[num_valid - 1] == 1) {
        // for (int i = 0; i < COUNT; i++) {     
        //   printf("%d ", valid[i]);
        // }
        
        pthread_exit(NULL);

      } else {
        valid_row[num_valid - 1] = 1;
      }

    }
  }

  valid[0] = 1;

  pthread_exit(NULL);
}

// Checks whether or not the columns contain numbers 1-9, if they do, then return 1
void * count_columns(void * data) {

  parameters *data_entry = (parameters *) data;
  int count_rows = data_entry->row;
  int count_columns = data_entry->column;
  int valid_columns[COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = count_columns; i < COUNT; i++) {

    for (int j = count_rows; j < COUNT; i++) {

      int num_valid = grid_numbers[j][i];

      if (num_valid < 0 || num_valid > 9 || valid_columns[num_valid - 1] == 1) {
        pthread_exit(NULL);

      } else {
        valid_columns[num_valid - 1] = 1;
      }

    }
  }

  valid[1] = 1;


  pthread_exit(NULL);
}

// Checks whether or not each of the 9 grids contain numbers 1-9, if they do, then return 1
void * validate_number(void * data) {

  parameters *data_entry = (parameters *) data;
  int count_rows = data_entry->row;
  int count_columns = data_entry->column;
  int valid_grid[COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = count_rows; i < count_rows + 3; i++) {

    for (int j = count_columns; j < count_columns + 3; j++) {

      int num_valid = grid_numbers[i][j];

      if (num_valid < 0 || num_valid > 9 || valid_grid[num_valid - 1] == 1) {
        pthread_exit(NULL);

      } else {
        valid_grid[num_valid - 1] = 1;
      }

    }
  }

  for (int i = 2; i < COUNT+2; i++) {
      valid[i] = 1;
  }

  pthread_exit(NULL);
}
