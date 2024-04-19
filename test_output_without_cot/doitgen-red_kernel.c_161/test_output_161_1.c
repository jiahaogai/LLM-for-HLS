#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 30; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 30; j++) {
      sum[i] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 20; k++) {
        sum[i] += A[i][k][j] * C4[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 30; i++) {
    for (j = 0; j < 30; j++) {
      C4[i][j] = sum[i] + 1.0;
    }
  }
//#pragma endscop
}