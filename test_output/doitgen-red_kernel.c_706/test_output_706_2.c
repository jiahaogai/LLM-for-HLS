#pragma ACCEL kernel

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
    
#pragma ACCEL TILE FACTOR=auto{4}
    for (q = 0; q < 20; q++) {
      double sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
      for (p = 0; p < 25; p++) {
        sum_tmp += A[p][q][r] * C4[p][r];
      }
      sum[q] = sum_tmp;
    }
    for (s = 0; s < 30; s++) {
      A[r][s][q] = sum[s];
    }
  }
//#pragma endscop
}