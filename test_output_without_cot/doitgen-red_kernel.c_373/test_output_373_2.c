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
    
#pragma ACCEL TILE FACTOR=auto{20}
    for (q = 0; q < 30; q++) {
      sum[q] = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (p = 0; p < 20; p++) {
        for (s = 0; s < 30; s++) {
          sum[q] = sum[q] + A[r][p][s] * C4[p][q];
        }
      }
    }
  }
//#pragma endscop
}