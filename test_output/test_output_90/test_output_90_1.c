
//#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][25][20],double sum[25][20])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        sum[r][q] += A[r][q][p] * C4[p][r][q];
      }
    }
  }
//#pragma endscop
}
