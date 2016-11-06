/* Hello World program */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

static void copyWorld(MatrixPtr* srcMatrixPtr, MatrixPtr* dstMatrixPtr)
{
  unsigned int i;
  unsigned int j;

  for (i = 0; i < ROWS; ++i)
  {
    for (j = 0; j < COLS; ++j)
    {
      dstMatrixPtr[i][j] = srcMatrixPtr[i][j];
    }
  }
}

static void evolveWorld()
{
// Add code here

}



int main()
{

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
