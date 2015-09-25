/****************************************************/
/* Name: Cyriac Domini Thundathil                   */
/* Lab 1                                            */
/* Last Updated: 9/21/2015                          */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>

void printmatrix(double *m, int n){
  int r=0, c=0;
  printf("\n");
  for(r=0;r<n;r++){
    printf("[");
    for(c=0;c<n;c++){
      printf("%.3f ",*((double *)m + r*n+c));
    }
    printf("]\n");
  }
}

void printarr(double *c, int n){
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
      double sum = 0;
      for(k=0;k<dim;k++){
        a=((char*)A +(i*size*dim) + (k*size));
        b=((char*)B +(k*size*dim) + (j*size));
        sum=sum+(*(double*)a)*(*(double*)b);
      }
      *((double*)C +(i*dim) +j)=sum;
    }
  }
}

void solveMatrix(void *m, void *y, void *x, int n, int size, char type){
  double* e1 = (double *)malloc(n*n*sizeof(double));
  double* e2 = (double *)malloc(n*n*sizeof(double));
  double* ans = (double *)malloc(n*n*sizeof(double));
  double* m2 = (double *)malloc(n*n*sizeof(double));
  double* y2 = (double *)malloc(n*sizeof(double));
  double* x2 = (double *)malloc(n*sizeof(double));
  double sum=0;
  int i=0,c=0,r=0, j=0;
  if (type == 'i'){
    for(c=0;c<n;c++){
      for(r=0;r<n;r++){
        *(m2+r*n+c) = (double)(*(int*)((char*)m + (r*size*n) + (c*size)));
      }
      *(y2+c) = (double)(*(int*)((char*)(y + (c*size))));
    }
  }else if(type == 'f'){
    for(c=0;c<n;c++){
      for(r=0;r<n;r++){
        *(m2+r*n+c) = (double)(*(float*)((char*)m + (r*size*n) + (c*size)));
      }
      *(y2+c) = (double)(*(float*)((char*)(y + (c*size))));
    }
  }else if(type == 's'){
    for(c=0;c<n;c++){
      for(r=0;r<n;r++){
        *(m2+r*n+c) = (double)(*(short*)((char*)m + (r*size*n) + (c*size)));
      }
      *(y2+c) = (double)(*(short*)((char*)(y + (c*size))));
    }
  }else if(type == 'l'){
    for(c=0;c<n;c++){
      for(r=0;r<n;r++){
        *(m2+r*n+c) = (double)(*(long*)((char*)m + (r*size*n) + (c*size)));
      }
      *(y2+c) = (double)(*(long*)((char*)(y + (c*size))));
    }
  }else {
    for(c=0;c<n;c++){
      for(r=0;r<n;r++){
        *(m2+r*n+c) = (*(double*)((char*)m + (r*size*n) + (c*size)));
      }
      *(y2+c) = (*(double*)((char*)(y + (c*size))));
    }
  }
  for (i=0;i<n;i++){
    *((double *)e1 + i*n+i) = 1.0;
    *((double *)e2 + i*n+i) = 1.0;
  }
  for (c=0;c<n;c++){
    *((double *)e1 + c*n+c) = 1/(*((double *)m2 + c*n+c));
    *(y2+c)=*(y2+c) * *((double *)e1 + c*n+c);
    multiply(e1,m2,ans,sizeof(double),n,'f');
    m2=ans;
    for(r=c+1;r<n;r++){
      *((double *)e2 + r*n+c) = -1*(*((double *)m2 + r*n+c));
      for(i=0;i<n;i++){
        sum = sum + *(y2+i)**((double *)e2 + r*n+i);
      }
      *(y2+r)=sum;
      sum = 0;
      multiply(e2,m2,ans,sizeof(double),n,'f');
      m2=ans;
      *((double *)e2 + r*n+c) = 0;
    }
    *((double *)e1 + c*n+c) = 1;
  }
  for(i=n-1;i>=0;i--){
    sum = 0;
    for(j=n-1;j>i;j--){
      sum += *(x2+j) * *((double *)m2 + i*n+j);
    }
    *(x2+i) = *(y2+i)-sum;
  }
  if(type == 'f'){
    for(i=0;i<n;i++){
      (*(float*)((char*)(x+i*size))) = *(x2 + i);
    }
  }else if(type == 'i'){
    for(i=0;i<n;i++){
      (*(int*)((char*)(x+i*size))) = *(x2 + i);
    }
  }else if(type == 's'){
    for(i=0;i<n;i++){
      (*(short*)((char*)(x+i*size))) = *(x2 + i);
    }
  }else if(type == 'l'){
    for(i=0;i<n;i++){
      (*(long*)((char*)(x+i*size))) = *(x2 + i);
    }
  }else{
    for(i=0;i<n;i++){
      (*(double*)((char*)(x+i*size))) = *(x2 + i);
    }
  }
}

int main ()
{
  /*Set up counter variables */
  int r = 0, c = 0, n = 4, i=0;

  float m1[4][4];
  float x[4];
  float mat[16]={2,5,-9,3,5,6,-4,2,3,-4,2,7,11,7,4,-8};
  float y[4]={151,103,16,-32};

  // long m1[3][3];
  // long x[3];
  // long mat[9]={2,3,4,3,2,1,1,2,2};
  // long y[3]={29,16,16};

  // short m1[3][3];
  // short x[3];
  // short mat[9]={2,3,4,3,2,1,1,2,2};
  // short y[3]={29,16,16};

  // int m1[3][3];
  // int x[3];
  // int mat[9]={2,3,4,3,2,1,1,2,2};
  // int y[3]={29,16,16};

  // double m1[3][3];
  // double x[3];
  // double mat[9]={2,3,4,3,2,1,1,2,2};
  // double y[3]={29,16,16};

  for(r=0;r<n;r++){
    for(c=0;c<n;c++){
      m1[r][c] = mat[i];
      i++;
      x[c]=0;
    }
  }
  solveMatrix(&m1[0][0],&y[0],&x[0],n,sizeof(float),'f');
  printf("\n[");
  for(i=0;i<n;i++){
    printf("%.3f ", x[i] );
  }
  printf("]\n");
}
