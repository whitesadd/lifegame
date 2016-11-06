/* Hello World program */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<assert.h>

#define ROWS (20)
#define COLS (32)


char matrix1[ROWS][COLS];
char matrix2[ROWS][COLS];

typedef char MatrixPtr[COLS];

MatrixPtr* matrixPtr1 = matrix1;
MatrixPtr* matrixPtr2 = matrix2;

static void initializeWorld(MatrixPtr* matrixPtr)
{
  unsigned int i;
  unsigned int j;
  unsigned int insertionRow = ROWS / 2;
  unsigned int firstColumn = COLS / 2 - 5;

  for (i = 0; i < ROWS; ++i)
  {
    for (j = 0; j < COLS; ++j)
    {
      matrixPtr[i][j] = 0;
    }
  }

  for (j = firstColumn; j < firstColumn + 10; ++j)
  {
    matrixPtr[insertionRow][j] = 1;
  }
}

static void printWorld(MatrixPtr* matrixPtr)
{
  unsigned int i;
  unsigned int j;

  for (i = 0; i < ROWS; ++i)
  {
    for (j = 0; j < COLS; ++j)
    {
      putchar(32 + matrixPtr[i][j] * 10);
    }
    putchar('\n');
  }
}

int get_cell_state(MatrixPtr* universe, int i, int j)
{
  if (i < 0) return 0;
  if (j < 0) return 0;
  if (i >= ROWS) return 0;
  if (j >= COLS) return 0;
  return universe[i][j];
}

static void evolveWorld()
{
  int i, j;

  for (i = 0; i < ROWS; ++i)
  {
    for (j = 0; j < COLS; ++j)
    {
      // count neighbors
      int count = 0;

      if (get_cell_state(matrixPtr1, i - 1, j - 1) == 1) count++;
      if (get_cell_state(matrixPtr1, i - 1, j) == 1) count++;
      if (get_cell_state(matrixPtr1, i - 1, j + 1) == 1) count++;
      if (get_cell_state(matrixPtr1, i, j - 1) == 1) count++;
      if (get_cell_state(matrixPtr1, i, j + 1) == 1) count++;
      if (get_cell_state(matrixPtr1, i + 1, j - 1) == 1) count++;
      if (get_cell_state(matrixPtr1, i + 1, j) == 1) count++;
      if (get_cell_state(matrixPtr1, i + 1, j + 1) == 1) count++;

      // Any live cell with fewer than two live neighbours dies, as if caused by under-population.
      if (matrixPtr1[i][j] == 1 && count < 2)
      {
        matrixPtr2[i][j] = 0;
      }

      // Any live cell with two or three live neighbours lives on to the next generation.
      else if (matrixPtr1[i][j] == 1 && count <= 3)
      {
        matrixPtr2[i][j] = 1;
      }

      // Any live cell with more than three live neighbours dies, as if by over-population.
      else if (matrixPtr1[i][j] == 1)
      {
        matrixPtr2[i][j] = 0;
      }

      // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
      else if (matrixPtr1[i][j] == 0 && count == 3)
      {
        matrixPtr2[i][j] = 1;
      }

      else if (matrixPtr1[i][j] == 0)
      {
        matrixPtr2[i][j] = 0;
      }

      // Just in case - it should not happen
      else
      {
        assert(0);
      }
    }
  }

  // Switch Matrices pointers
  MatrixPtr* matrixTmpPtr = matrixPtr1;
  matrixPtr1 = matrixPtr2;
  matrixPtr2 = matrixTmpPtr;
}


#ifdef TEST_ON
static void run_tests()
{
    assert(1);
}
#endif


int main()
{

#ifdef TEST_ON
    run_tests();
#endif

    unsigned int i;
    clock_t start, end;
    initializeWorld(matrixPtr1);
    start = clock();
    for (i = 0; i < 100000; ++i)
    {
      evolveWorld();
    }
    end = clock();

    printf("Final world\n\n");
    printWorld(matrixPtr1);
    printf("Time needed was %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    return 0;

}
