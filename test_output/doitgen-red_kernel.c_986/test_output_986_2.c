#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (q = 0; q < 20; q++) {
      double tmp = A[r][q][0];
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L2}
      for (p = 1; p < 30; p++) {
        tmp += A[r][q][p];
      }
      for (s = 0; s < 30; s++) {
        C4[s][q] = tmp * C4[s][q];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (s = 0; s < 30; s++) {
      double sum_tmp = sum[s];
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L3}
      for (q = 0; q < 20; q++) {
        for (p = 0; p < 30; p++) {
          sum_tmp += A[r][q][p] * C4[p][q];
        }
      }
      sum[s] = sum_tmp;
    }
  }
//#pragma endscop
}