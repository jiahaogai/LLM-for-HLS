#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[25][25][30][35],double sum[30][35])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 25; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        for (s = 0; s < 35; s++) {
          sum[p][s] += A[r][p][s] * C4[q][r][p][s];
        }
      }
    }
    for (s = 0; s < 35; s++) {
      for (p = 0; p < 30; p++) {
        A[r][p][s] = sum[p][s];
      }
    }
  }
//#pragma endscop
}