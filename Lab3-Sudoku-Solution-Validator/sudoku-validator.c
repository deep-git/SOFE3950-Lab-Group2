#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    int row;
    int column;
} parameters;

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

int * count_rows(void * data);
int * count_columns(void * data);

int main (void) {

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

    pthread_create(&t_row, NULL, count_rows, (int *) data0);
    pthread_create(&t_col, NULL, count_columns, (int *) data0);
    pthread_create(&t_1, NULL, validate_number, (void *) data1);
    pthread_create(&t_2, NULL, validate_number, (void *) data2);
    pthread_create(&t_3, NULL, validate_number, (void *) data3);
    pthread_create(&t_4, NULL, validate_number, (void *) data4);
    pthread_create(&t_5, NULL, validate_number, (void *) data5);
    pthread_create(&t_6, NULL, validate_number, (void *) data6);
    pthread_create(&t_7, NULL, validate_number, (void *) data7);
    pthread_create(&t_8, NULL, validate_number, (void *) data8);
    pthread_create(&t_9, NULL, validate_number, (void *) data9);

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

    if ((int) rows == 1 && (int) columns == 1 && (int) grid1 == 1 && (int) grid2 == 1 && (int) grid3 == 1 && (int) grid4 == 1 && (int) grid5 == 1 && (int) grid6 == 1 &&
    (int) grid7 == 1 && (int) grid8 == 1 && (int) grid9 == 1) {
        printf("The sudoku puzzle was solved successfully, congratulations!");
    } else {
        printf("The sudoku puzzle is not solved correctly, please try again");
    }

    return 0;
}

// Checks whether or not the rows contain numbers 1-9, if they do, then return 1
int * count_rows(void * data) {

    /*
    for (int i = 0; i < 9; i++) {
        if (sudoku_board[rows][i] < 0 || sudoku_board[rows][i] > 0) {
            return -1;
        } else {
            if (sudoku_board[rows][i] != 0) {

            }
        }
    }
    */
}

// Checks whether or not the columns contain numbers 1-9, if they do, then return 1
int * count_columns(void * data) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j <= 9; j++) {
            int count = 0;
            for (int k = 0; k < 9; k++) {
                if (sudoku_board[k][i] == j) {
                    if (count > 0) {
                        return 0;
                    }
                    count = 1;
                }
            }
        }
    }

    return 1;

}

// Checks whether or not each of the 9 grids contain numbers 1-9, if they do, then return 1
void * validate_number(void * data) {

}
