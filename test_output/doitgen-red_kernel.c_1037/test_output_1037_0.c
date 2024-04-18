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
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      double sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{2}
      for (p = 0; p < 20; p++) {
        sum_tmp += A[r][p][q] * C4[p][q];
      }
      sum[q] = sum_tmp;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (q = 0; q < 30; q++) {
      A[r][0][q] = sum[q];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (p = 1; p < 20; p++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3_0}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3_0}
      for (q = 0; q < 30; q++) {
        A[r][p][q] = A[r][p][q] * A[r][0][q];
      }
    }
  }
//#pragma endscop
}