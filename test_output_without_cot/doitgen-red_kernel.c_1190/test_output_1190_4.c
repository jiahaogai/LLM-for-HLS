#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
  double temp;
  double sum_tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 0; q < 20; q++) {
      sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
      loop_p:
      for (p = 0; p < 30; p++) {
        temp = A[r][q][p] * C4[p][q];
        sum_tmp += temp;
      }
      sum[r] = sum_tmp;
    }
    loop_s:
    for (s = 0; s < 30; s++) {
      A[r][5][s] = sum[s] + 3.14;
    }
  }
}