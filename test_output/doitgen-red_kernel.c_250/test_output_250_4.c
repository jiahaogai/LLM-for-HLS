#pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][30],int sum[30])
{
  int r;
  int q;
  int p;
  int s;
  int r_col;
  int tmp;
  int tmp_row;
  int product;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_r:
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loop_q:
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      loop_p:
      for (p = 0; p < 30; p++) {
        tmp_row = 0;
        loop_s:
        for (s = 0; s < 30; s++) {
          tmp_row += A[r][q][s] * C4[s][p];
        }
        sum[p] = tmp_row;
      }
      tmp_row = sum[0] + sum[1] + sum[2];
      loop_r_col:
      for (r_col = 0; r_col < 25; r_col++) {
        product = A[r_col][q][p] * tmp_row;
        A[r_col][q][p] = product;
      }
    }
  }
}