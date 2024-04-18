c
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
    double sum_tmp = (double )0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_q:
    for (q = 0; q < 20; q++) {
      loop_p:
      for (p = 0; p < 30; p++) {
        sum_tmp += A[r][q][p] * C4[p][q];
      }
    }
    sum[r] = sum_tmp;
  }
  loop_s:
  for (s = 0; s < 30; s++) {
    temp = 0.0;
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_r_1:
    for (r = 0; r < 25; r++) {
      temp += A[r][s][0] * sum[r];
    }
    sum[s] = temp;
  }
}