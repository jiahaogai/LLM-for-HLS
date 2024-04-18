#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[25][25][30][35],double sum[25][35])
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
    for (q = 0; q < 25; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
      for (p = 0; p < 30; p++) {
        sum[r][0] += A[r][p][q] * C4[p][q][0][s] ;
      }
    }
    for (s = 1; s < 35; s++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        sum[r][s] = sum[r][s - 1] + A[r][p][q] * C4[p][q][s][s] ;
      }
    }
  }
//#pragma endscop
}