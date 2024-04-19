#include <math.h>
#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      sum[0] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      for (s = 0; s < 30; s++) {
        sum[0] += A[r][q][s];
      }
      C4[0][q] = sum[0];
      sum[s] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (s = 0; s < 30; s++) {
        sum[s] += A[r][q][s] * C4[s][q];
      }
      for (s = 0; s < 30; s++) {
        A[r][q][s] = sum[s];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (p = 0; p < 30; p++) {
      sum[p] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L2}
      for (q = 0; q < 20; q++) {
        sum[p] += A[r][q][p];
      }
    }
  }
//#pragma endscop
}