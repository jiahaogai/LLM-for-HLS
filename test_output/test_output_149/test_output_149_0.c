
 #pragma ACCEL kernel

void kernel_3mm(double A[25][20][30],double B[25][30][40],double C[20][30][40],double D[25][30][50],double E[25][40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 40; k++) {
        A[i][j][k] = 0.0;
        for (int n = 0; n < 20; n++) {
          A[i][j][k] += B[i][n][k] * C[n][j][k];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (j = 0; j < 30; j++) {
      for (k = 0; k < 50; k++) {
        E[i][j][k] = 0.0;
        for (int n = 0; n < 40; n++) {
          E[i][j][k] += A[i][j][n] * D[i][n][k];
        }
      }
    }
  }
//#pragma endscop
}
