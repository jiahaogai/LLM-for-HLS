#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[25][20][30],double B[25][30][40],double C[30][40][50],double D[20][40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{25}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        A[i][j][k] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 30; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 40; k++) {
        for (l = 0; l < 50; l++) {
          A[i][j][k] += B[i][k][l] * C[j][k][l];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 50; k++) {
        double sum = D[i][j][k];
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        for (l = 0; l < 30; l++) {
          sum += A[l][i][k] * B[l][k][j];
        }
        D[i][j][k] = sum;
      }
    }
  }
//#pragma endscop
}