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

static void evolveWorld(void)
{
// Add code here
	int i, j, numalive;
	int rowst, colst, rowend, colend;

	for (i = 1; i < (ROWS -1); i++){
		for (j = 1; j < (COLS -1); j++){
			rowend = i+1;
			colend = j+1;
			numalive = 0;

			for (rowst = i-1; rowst <= rowend; rowst++){
				for (colst = j-1; colst <= colend; colst++){
					numalive = numalive + matrixPtr1[rowst][colst];
				}
			}
			numalive = numalive - matrixPtr1[i][j];

			if (matrixPtr1[i][j] == 1){
				if(numalive < 2 || numalive > 3){
					matrixPtr2[i][j] = 0;
				}
				else{
					matrixPtr2[i][j] = 1;
				}
			}
			else{
				if(numalive == 3)
					matrixPtr2[i][j] = 1;
				else
					matrixPtr2[i][j] = 0;
			}
		}
	}
}

static void evolveWorldopt(void)
{
// Add code here
	int i, j, numalive;
	int rowst, colst, rowend, colend;

	for (i = 1; i < (ROWS -1); i++){
		for (j = 1; j < (COLS -1); j++){
			rowend = i+1;
			colend = j+1;
			numalive = 0;

			for (rowst = i-1; rowst <= rowend; rowst++){
				for (colst = j-1; colst <= colend; colst++){
					numalive = numalive + matrixPtr1[rowst][colst];
				}
			}
			numalive = matrixPtr1[i-1][j-1] + matrixPtr1[i-1][j] + matrixPtr1[i-1][j+1] + matrixPtr1[i][j-1] + matrixPtr1[i][j+1]
			           + matrixPtr1[i+1][j-1] + matrixPtr1[i+1][j] + matrixPtr1[i+1][j+1];

			if (matrixPtr1[i][j] == 1){
				if(numalive < 2 || numalive > 3){
					matrixPtr2[i][j] = 0;
				}
				else{
					matrixPtr2[i][j] = 1;
				}
			}
			else{
				if(numalive == 3)
					matrixPtr2[i][j] = 1;
				else
					matrixPtr2[i][j] = 0;
			}
		}
	}
}


int main(void)
{
   
    unsigned int i;
    clock_t start, end;
    MatrixPtr* matrixPtr3;
    /* No optimizations */
    initializeWorld(matrixPtr1);
    printWorld(matrixPtr1);
    start = clock();

    for (i = 0; i < 100000; ++i)
    {
      evolveWorld();
      copyWorld(matrixPtr2, matrixPtr1);
    }
    end = clock();
    
    printf("No optimization : Final world\n\n");
    printWorld(matrixPtr1);
    printf("No optimization : Time needed was %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    
    /* opt1 changing pointers */
    initializeWorld(matrixPtr1);
    printWorld(matrixPtr1);
    start = clock();

    for (i = 0; i < 100000; ++i)
    {
      evolveWorld();
      
      matrixPtr3 = matrixPtr1;
      matrixPtr1 = matrixPtr2;
      matrixPtr2 = matrixPtr3;
    }
    end = clock();
    
    printf("Interchange pointers : Final world\n\n");
    printWorld(matrixPtr1);
    printf("Interchange pointers : Time needed was %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    
    /* opt2 unwind loop only */
    initializeWorld(matrixPtr1);
    printWorld(matrixPtr1);
    start = clock();

    for (i = 0; i < 100000; ++i)
    {
      evolveWorldopt();
      copyWorld(matrixPtr2, matrixPtr1);
    }
    end = clock();
    
    printf("Unwind loop only : Final world\n\n");
    printWorld(matrixPtr1);
    printf("Unwind loop only : Time needed was %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    
    /* opt3 changing pointers and unwind loop */
    initializeWorld(matrixPtr1);
    printWorld(matrixPtr1);
    start = clock();

    for (i = 0; i < 100000; ++i)
    {
      evolveWorldopt();
      
      matrixPtr3 = matrixPtr1;
      matrixPtr1 = matrixPtr2;
      matrixPtr2 = matrixPtr3;
    }
    end = clock();
    
    printf("Unwind loop and Interchange pointers : Final world\n\n");
    printWorld(matrixPtr1);
    printf("Unwind loop and Interchange pointers : Time needed was %f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    return 0;
}
