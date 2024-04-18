#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{20}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (s = 0; s < 30; s++) {
        sum[s] = ((double )0);
        for (p = 0; p < 30; p++) {
          sum[s] += A[r][q][p] * C4[p][s];
        }
      }
      for (s = 0; s < 30; s++) {
        A[r][q][s] = sum[s];
      }
    }
  }
//#pragma endscop
}