#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
  double temp1;
  double mul1;
  double sum_tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 0; q < 20; q++) {
      sum_tmp = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
      loop_p:
      for (p = 0; p < 30; p++) {
        temp1 = A[r][q][p];
        mul1 = temp1 * C4[p][q];
        sum_tmp += mul1;
      }
      sum[r] = sum_tmp;
    }
  }
}