#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
  double temp;
  double mul1;
  double mul2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{25}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 0; q < 20; q++) {
      temp = A[r][q][0];
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      loop_s:
      for (s = 0; s < 30; s++) {
        mul1 = temp * C4[s][q];
        loop_p:
        for (p = 0; p < 30; p++) {
          mul2 = mul1 * C4[p][s];
          sum[s] += mul2;
        }
      }
    }
  }
}