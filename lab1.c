/****************************************************/
/* Name: Cyriac Domini Thundathil                   */
/* Lab 1                                            */
/* Last Updated: 9/21/2015                          */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatrix(){
  /*add print fucntion*/
}

void multiply(){
  /*generic multiply function*/
}

int main ()
{
  /*Set up counter variables */
  int r = 0, c = 0, n = 3;
  float matrix[3][3];
  for(r=0;r<n;r++){
    for(c=0;c<n;c++){
      printf("Enter %i, %i: ", r,c );
      scanf("%f",&matrix[r][c] );
    }
  }
  for(r=0;r<n;r++){
    for(c=0;c<n;c++){
      printf("[%f] ", matrix[r][c] );
    }
    printf("\n");
  }
}
