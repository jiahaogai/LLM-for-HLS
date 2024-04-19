#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      double sum_tmp = (double )0;
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
      for (s = 0; s < 30; s++) {
        sum_tmp += A[r][q][s] * C4[s][q];
      }
      sum[r] = sum_tmp;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    for (p = 0; p < 30; p++) {
      double tmp = (double )0;
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (s = 0; s < 30; s++) {
        tmp += A[r][s][p] * sum[s];
      }
      C4[p][0] = tmp;
    }
  }
//#pragma endscop
}