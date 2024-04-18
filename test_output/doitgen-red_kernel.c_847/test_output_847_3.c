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
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    for (q = 0; q < 20; q++) {
      double sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
      for (p = 0; p < 25; p++) {
        sum_tmp += A[p][q][r] * C4[p][r];
      }
      sum[q] = sum_tmp;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (s = 0; s < 30; s++) {
      A[r][0][s] = sum[0] * C4[0][s];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (p = 1; p < 20; p++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      for (s = 0; s < 30; s++) {
        A[r][p][s] = sum[p] * C4[p][s];
      }
    }
  }
//#pragma endscop
}