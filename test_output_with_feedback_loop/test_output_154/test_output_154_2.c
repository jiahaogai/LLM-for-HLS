#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define NR_END 1
#define FREE_ARG char*

#define NI 64
#define NJ 64
#define NK 64
#define NL 64
#define NT 4
#define REAL double

void kernel_dpbsp(int tsteps,int n,REAL A[40][50][60][50],REAL B[40][50][60][50],REAL F[40][60][50][50],REAL J[40][50][50][50],REAL D[60][50][50],REAL C[60][50][50])
{
  int t;
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (i = 0; i <= 39; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (j = 0; j <= 29; j++) {
        for (k = 0; k <= 29; k++) {
          A[i][j][k][l] = 0.0;
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (t = 0; t <= 38; t++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (i = 0; i <= 39; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      for (j = 0; j <= 29; j++) {
        for (k = 0; k <= 29; k++) {
          for (l = 0; l <= 29; l++) {
            A[i][j][k][l] = (REAL )(((long )j) * ((long )k) * ((long )l));
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (i = 0; i <= 39; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      for (j = 0; j <= 29; j++) {
        for (k = 0; k <= 29; k++) {
          for (l = 0; l <= 29; l++) {
            F[i][j][k][l] = 0.0;
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    for (i = 0; i <= 39; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L8}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
      for (j = 0; j <= 29; j++) {
        for (k = 0; k <= 29; k++) {
          for (l = 0; l <= 29; l++) {
            J[i][j][k][l] = 0.0;
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    for (i = 0; i <= 59; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L10}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
      for (j = 0; j <= 49; j++) {
        for (k = 0; k <= 49; k++) {
          D[i][j][k] = 0.0;
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L11}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L11}
    for (i = 0; i <= 59; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L12}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L12}
      for (j = 0; j <= 49; j++) {
        for (k = 0; k <= 49; k++) {
          C[i][j][k] = 0.0;
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L13}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L13}
    for (t = 0; t <= 37; t++) {
      
      for (i = 0; i <= 39; i++) {
        for (j = 0; j <= 29; j++) {
          for (k = 0; k <= 29; k++) {
            for (l = 0; l <= 29; l++) {
              F[i][j][k][l] += A[i][j][k][l] * B[i][j][k][l];
            }
          }
        }
      }
      
      for (i = 0; i <= 39; i++) {
        for (j = 0; j <= 29; j++) {
          for (k = 0; k <= 29; k++) {
            for (l = 0; l <= 29; l++) {
              J[i][j][k][l] = F[i][j][k][l] - J[i][j][k][l];
            }
          }
        }
      }
      
      for (i = 0; i <= 59; i++) {
        for (j = 0; j <= 49; j++) {
          for (k = 0; k <= 49; k++) {
            double _in_8 = (double )(60.0 * 50.0 * 40.0);
            double _in_9 = (double )(j * k * l);
            double _in_10 = J[i][j][k][l];
            D[i][j][k] += _in_8 * _in_9 * _in_10;
          }
        }
      }
      
      for (i = 0; i <= 59; i++) {
        for (j = 0; j <= 49; j++) {
          for (k = 0; k <= 49; k++) {
            double _in_11 = D[i][j][k];
            C[i][j][k] += _in_11;
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L14}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L14}
    for (i = 0; i <= 39; i++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L15}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L15}
      for (j = 0; j <= 29; j++) {
        for (k = 0; k <= 29; k++) {
          for (l = 0; l <= 29; l++) {
            F[i][j][k][l] = C[i][j][k] + J[i][j][k][l];
          }
        }
      }
    }
    
  }
//#pragma endscop
}