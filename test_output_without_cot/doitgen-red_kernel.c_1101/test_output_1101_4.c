#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
  double temp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_q:
    for (q = 0; q < 30; q++) {
      temp = A[r][0][q];
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_p:
      for (p = 0; p < 20; p++) {
        loop_s:
        for (s = 0; s < 30; s++) {
          A[r][p][s] = A[r][p][s] * C4[s][q];
        }
        sum[q] += A[r][p][s] * temp;
      }
      A[r][0][q] = sum[q];
    }
  }
}