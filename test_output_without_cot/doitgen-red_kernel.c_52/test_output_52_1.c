#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
  int r_col;
  int tmp;
  int sum_tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_q:
    for (q = 0; q < 30; q++) {
      sum_tmp = ((int )0);
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_p:
      for (p = 0; p < 20; p++) {
        r_col = 0;
        loop_s:
        for (s = 0; s < 30; s++) {
          r_col += A[r][p][s] * C4[s][q];
        }
        tmp = r_col + sum[p];
        sum[p] = tmp;
        sum_tmp += tmp;
      }
      C4[q][r] = sum_tmp;
    }
  }
}