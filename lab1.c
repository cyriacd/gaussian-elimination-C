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
    printf("[");
    for(c=0;c<n;c++){
      printf("%.3f ",*((float *)m + r*n+c));
    }
    printf("]\n");
  }
}

void printarr(float *c, int n){
  int i=0;
  printf("[");
  for(i=0;i<n;i++){
    printf("%.3f ", *(c+i));
  }
  printf("]\n");
}

void multiply (void *A, void *B, void *C, int size, int dim, char type){
  //if type = 'i'
  int i,j,k;
  void *a, *b;
  for (i=0;i<dim;i++){
    for(j=0;j<dim;j++){
      float sum = 0;
      for(k=0;k<dim;k++){
        a=((char*)A +(i*size*dim) + (k*size));
        b=((char*)B +(k*size*dim) + (j*size));
        sum=sum+(*(float*)a)*(*(float*)b);
      }
      *((float*)C +(i*dim) +j)=sum;
    }
  }
}

void solveMatrix(float *m, float *y, float *x, int n){
  float* e1= (float *)malloc(n*n*sizeof(float));
  float* e2= (float *)malloc(n*n*sizeof(float));
  float* ans= (float *)malloc(n*n*sizeof(float));
  float sum=0;
  int i=0,c=0,r=0, j=0;
  for (i=0;i<n;i++){
    *((float *)e1 + i*n+i) = 1.0;
    *((float *)e2 + i*n+i) = 1.0;
  }
  for (c=0;c<n;c++){
    *((float *)e1 + c*n+c) = 1/(*((float *)m + c*n+c));
    *(y+c)=*(y+c) * *((float *)e1 + c*n+c);
    // printf("e1start:");
    // printmatrix(e1,n);
    // printarr(y,n);
    multiply(e1,m,ans,sizeof(float),n,'f');
    m=ans;
    // printmatrix(m,n);
    for(r=c+1;r<n;r++){
      *((float *)e2 + r*n+c) = -1*(*((float *)m + r*n+c));
      for(i=0;i<n;i++){
        sum = sum + *(y+i)**((float *)e2 + r*n+i);
      }
      *(y+r)=sum;
      sum = 0;
      // printf("e2:");
      // printmatrix(e2,n);
      // printarr(y,n);
      multiply(e2,m,ans,sizeof(float),n,'f');
      m=ans;
      *((float *)e2 + r*n+c) = 0;
    }
    *((float *)e1 + c*n+c) = 1;
  }
  printf("Upper Triangular Matrix: ");
  printmatrix(m,n);
  printf("Upper Triangular Coeff: ");
  printarr(y,n);

  for(i=n-1;i>=0;i--){
    sum = 0;
    for(j=n-1;j>i;j--){
      sum += *(x+j) * *((float *)m + i*n+j);
    }
    *(x+i) = *(y+i)-sum;
  }
  printf("FINAL X values: ");
  printarr(x,n);
}

int main ()
{
  /*Set up counter variables */
  int r = 0, c = 0, n = 3, i=0;
  float m1[3][3];
  float x[3];
  float mat[9]={1,1,1,0,2,5,2,5,-1};
  float y[3]={6,-4,27};
  for(r=0;r<n;r++){
    for(c=0;c<n;c++){
      m1[r][c] = mat[i];
      i++;
      x[c]=0;
    }
  }
  solveMatrix(&m1[0][0],&y[0],&x[0],n);
}
