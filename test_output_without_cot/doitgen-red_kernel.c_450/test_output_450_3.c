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
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (q = 0; q < 25; q++) {
      for (s = 0; s < 30; s++) {
        sum[s] = ((double )0);
        for (p = 0; p < 20; p++) {
          sum[s] += A[q][p][s] * C4[p][r];
        }
      }
    }
    for (s = 0; s < 30; s++) {
      A[24][0][s] = sum[s];
    }
  }
//#pragma endscop
}