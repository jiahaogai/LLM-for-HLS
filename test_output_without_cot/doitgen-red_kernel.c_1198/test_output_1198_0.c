- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Automatically parallelize the middle loop.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Automatically parallelize the outer loop.


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
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (p = 0; p < 30; p++) {
        sum[p] = ((double )0);
      }
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{30}
      for (s = 0; s < 30; s++) {
        for (p = 0; p < 30; p++) {
          sum[s] = sum[s] + A[r][q][p] * C4[p][s];
        }
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        A[r][q][p] = sum[p];
      }
    }
  }
//#pragma endscop
}