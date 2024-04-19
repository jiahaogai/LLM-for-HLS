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
  
#pragma ACCEL TILE FACTOR=auto{8}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    loop_q:
    for (q = 0; q < 20; q++) {
      r_col = 0;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      loop_p:
      for (p = 0; p < 30; p++) {
        sum_tmp = 0;
        
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L3}
        loop_s:
        for (s = 0; s < 30; s++) {
          tmp = A[r][q][s] * A[s][q][p];
          r_col += tmp;
          sum_tmp += A[r][s][p] * tmp;
        }
        C4[p][q] = r_col;
        sum[p] = sum_tmp;
      }
    }
  }
}