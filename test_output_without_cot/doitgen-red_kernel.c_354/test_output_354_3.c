#include <math.h>
#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      for (p = 0; p < 30; p++) {
        for (s = 0; s < 30; s++) {
          if (s < (p + 1)) {
            A[r][q][s] = 0.0;
          }
          else {
            A[r][q][s] = sum[s] - C4[s][p] * A[r][q][p];
          }
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (p = 0; p < 30; p++) {
    sum[p] = 0.0;
    for (r = 0; r < 25; r++) {
      for (q = 0; q < 20; q++) {
        sum[p] += A[r][q][p] * C4[p][q];
      }
    }
  }
//#pragma endscop
}