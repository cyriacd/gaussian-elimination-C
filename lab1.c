/****************************************************/
/* Name: Cyriac Domini Thundathil                   */
/* Lab 1                                            */
/* Last Updated: 9/21/2015                          */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printmatrix(float *m, int n){
  int r=0, c=0;
  printf("\n");
  for(r=0;r<n;r++){
    for(c=0;c<n;c++){
      printf("[%f] ",*((float *)m + r*n+c));
    }
    printf("\n");
  }
}

void solveMatrix(float *m, int n){
  float* id= (float *)malloc(n*n*sizeof(int));
  float* e1= (float *)malloc(n*n*sizeof(int));
  float* e2= (float *)malloc(n*n*sizeof(int));
  int i=0,c=0,r=0;
  for (i=0;i<n;i++){
    *((float *)id + i*n+i) = 1.0;
  }
  e1 = id;
  e2=id;
  printf("id:");
  printmatrix(id,n);
  for (c=0;c<n;c++){
    *((float *)e1 + c*n+c) = 1/(*((float *)m + c*n+c));
    for(r=c+1;r<n;r++){
      *((float *)e2 + r*n+c) = -1*(*((float *)m + r*n+c));
      printf("e2:");
      printmatrix(e2,n);
      *((float *)e2 + r*n+c) = 0;
    }
    printf("e2:");
    printmatrix(e2,n);
    printf("e1:");
    printmatrix(e1,n);
    *((float *)e1 + c*n+c) = 1;
  }
  printf("e1:");
  printmatrix(e1,n);

}

int main ()
{
  /*Set up counter variables */
  int r = 0, c = 0, n = 4;
  float matrix[4][4];
  for(r=0;r<n;r++){
    for(c=0;c<n;c++){
      printf("Enter %i, %i: ", r,c );
      scanf("%f",((float *)matrix + r*n+c));
    }
  }
  printmatrix(&matrix[0][0],n);
  solveMatrix(&matrix[0][0],n);
}
