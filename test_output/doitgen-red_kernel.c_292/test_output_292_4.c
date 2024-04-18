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
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 0; q < 20; q++) {
      temp = A[r][q][0];
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_p:
      for (p = 0; p < 30; p++) {
        loop_s:
        for (s = 0; s < 30; s++) {
          mul1 = A[r][q][s + 0] * temp;
          mul2 = A[r][q][s + 1] * temp;
          sum[s] += mul1 + mul2;
        }
      }
      C4[q][0] = sum[0] + 1.0;
      C4[q][1] = sum[1] + 1.0;
      C4[q][2] = sum[2] + 1.0;
      C4[q][3] = sum[3] + 1.0;
    }
  }
}