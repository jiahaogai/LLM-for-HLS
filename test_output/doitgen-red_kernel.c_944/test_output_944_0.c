#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      sum[r] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      for (p = 0; p < 25; p++) {
        for (s = 0; s < 20; s++) {
          sum[r] += A[p][s][r] * C4[q][s];
        }
      }
      A[0][0][r] = ((double )1.0);
      A[0][19][r] = ((double )0.0);
      A[19][0][r] = ((double )0.0);
      A[19][19][r] = ((double )1.0);
    }
  }
//#pragma endscop
}