#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,int nm,double A[25][20][30],double B[20][30][40],double C[30][40][50],double D[50][60][70],double E[50][70][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        A[i][j][k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        B[i][j][k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 30; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 40; j++) {
      for (k = 0; k < 50; k++) {
        C[i][j][k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 60; j++) {
      for (k = 0; k < 70; k++) {
        D[i][j][k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 70; j++) {
      for (k = 0; k < 80; k++) {
        E[i][j][k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        double sum = ((double )0);
        for (m = 0; m < 20; m++) {
          sum += A[i][m][k] * B[m][j][k];
        }
        A[i][j][k] = sum;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        double sum = ((double )0);
        for (m = 0; m < 30; m++) {
          sum += A[i][m][k] * C[m][j][k];
        }
        B[i][j][k] = sum;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 30; i++) {
    for (j = 0; j < 40; j++) {
      for (k = 0; k < 50; k++) {
        double sum = ((double )0);
        for (m = 0; m < 40; m++) {
          sum += A[i][m][k] * D[m][j][k];
        }
        C[i][j][k] = sum;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    for (j = 0; j < 50; j++) {
      for (k = 0; k < 70; k++) {
        double sum = ((double )0);
        for (m = 0; m < 50; m++) {
          sum += A[i][m][k] * E[m][j][k];
        }
        D[i][j][k] = sum;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    for (j = 0; j < 60; j++) {
      for (k = 0; k < 80; k++) {
        double sum = ((double )0);
        for (m = 0; m < 70; m++) {
          sum += A[i][m][k] * F[m][j][k];
        }
        E[i][j][k] = sum;
      }
    }
  }
//#pragma endscop
}