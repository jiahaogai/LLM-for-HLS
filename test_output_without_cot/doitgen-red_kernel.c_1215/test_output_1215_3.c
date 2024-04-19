- `#pragma ACCEL PARALLEL FACTOR=auto{2}`: Automatically parallelize the middle loop with a parallelization factor of 2.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Automatically parallelize the outer loop with a parallelization factor of 1.



#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{20}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      for (s = 0; s < 30; s++) {
        sum[s] = 0.0;
        for (p = 0; p < 25; p++) {
          sum[s] = sum[s] + A[p][q][r] * C4[p * 25 + r];
        }
        A[r][q][s] = sum[s];
      }
    }
  }
//#pragma endscop
}