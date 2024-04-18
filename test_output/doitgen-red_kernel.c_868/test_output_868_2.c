#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,int nm,double A[25][20][30],double B[25][20][40],double C[40][30][50],double D[30][40][50],double E[25][30][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        A[i][j][k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 50; k++) {
        E[i][j][k] = 0.0;
        for (l = 0; l < 40; l++) {
          E[i][j][k] += A[i][j][l] * B[i][l][k];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 50; k++) {
        C[i][j][k] = ((double )0);
        for (l = 0; l < 25; l++) {
          C[i][j][k] += D[l][j][k] * E[l][i][k];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        double sum_tmp = 0.0;
        for (l = 0; l < 50; l++) {
          sum_tmp += C[k][j][l] * A[i][j][l];
        }
        sum[k] = sum_tmp;
      }
    }
  }
//#pragma endscop
}