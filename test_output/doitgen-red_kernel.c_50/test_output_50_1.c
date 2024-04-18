#pragma ACCEL kernel

void kernel_doitgen(double sum[30],double A[25][20][30],double C4[30][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 30; q++) {
      sum[r] = 0.0;
      for (p = 0; p < 25; p++) {
        for (s = 0; s < 20; s++) {
          sum[r] += A[p][s][r] * C4[q][s];
        }
      }
      sum[r] = sum[r] + q * 1.0;
    }
  }
//#pragma endscop
}