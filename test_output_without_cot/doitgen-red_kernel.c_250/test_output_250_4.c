#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
  int r_col;
  int tmp;
  int tmp_0;
  int tmp_1;
  int sum_tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_q:
    for (q = 0; q < 20; q++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L2}
      loop_p:
      for (p = 0; p < 30; p++) {
        tmp_0 = 0;
        
#pragma ACCEL PARALLEL reduction=tmp_0 FACTOR=auto{__PARA__L3}
        loop_s:
        for (s = 0; s < 30; s++) {
          tmp_1 = A[r][q][s] * C4[s][p];
          tmp_0 += tmp_1;
        }
        sum_tmp = tmp_0 + tmp;
        sum[p] = sum_tmp;
        tmp = sum[p];
      }
      r_col = tmp;
      A[r][q][0] = r_col;
    }
  }
}