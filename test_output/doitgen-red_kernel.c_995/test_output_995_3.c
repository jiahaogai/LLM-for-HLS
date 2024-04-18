#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
  int a;
  int b;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_q:
    for (q = 0; q < 30; q++) {
      sum[r] = 0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_p:
      for (p = 0; p < 20; p++) {
        
#pragma ACCEL PIPELINE auto{off}
        loop_s:
        for (s = 0; s < 25; s++) {
          a = 0;
          b = 0;
          a = ((int )((r + 1) * (q + 1)));
          b = ((int )((s + 1) * (p + 1)));
          sum[r] = sum[r] + A[s][p][q] * C4[b][r];
        }
      }
      C4[q][r] = sum[r] + a;
    }
  }
}