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
  int tmp_col;
  int not_flatten;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (q = 0; q < 20; q++) {
      tmp_row = r * 20 + q;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        sum[p] = 0.0;
        A[r][q][p] = 0.0;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (s = 0; s < 30; s++) {
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L3}
        for (p = 0; p < 30; p++) {
          sum[p] = 0.0;
          for (r_col = 0; r_col < 25; r_col++) {
            tmp = r_col * 20 + s;
            sum[p] += A[r_col][q][p] * C4[tmp][r];
          }
          A[r][q][s] = sum[p];
        }
      }
    }
  }
}