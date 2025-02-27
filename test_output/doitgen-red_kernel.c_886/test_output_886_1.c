#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      double tmp = A[r][q][0];
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (p = 1; p < 30; p++) {
        tmp += A[r][q][p];
      }
      sum[q] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (s = 0; s < 30; s++) {
      double tmp = C4[s][0] * sum[0];
      
#pragma ACCEL PARALLEL reduction=C4_tmp FACTOR=auto{1}
      for (p = 1; p < 20; p++) {
        tmp += C4[s][p] * sum[p];
      }
      C4[s][0] = tmp;
    }
  }
//#pragma endscop
}