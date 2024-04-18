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
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      double tmp = A[r][q][0];
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (p = 1; p < 30; p++) {
        double tmp_p = A[r][q][p];
        sum[p] += tmp * C4[p * 20 + q];
      }
      sum[0] += tmp * C4[q];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  for (s = 0; s < 30; s++) {
    sum[s] = sum[s] + 1.0;
  }
//#pragma endscop
}