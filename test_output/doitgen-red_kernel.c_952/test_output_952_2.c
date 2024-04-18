#pragma ACCEL kernel

void kernel_doitgen(double sum[30],double A[25][20][30],double C4[30][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 25; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 20; p++) {
        for (s = 0; s < 30; s++) {
          sum[s] += A[q][p][s] * C4[r][s];
        }
      }
    }
    for (s = 0; s < 30; s++) {
      C4[r][s] = sum[s];
    }
  }
//#pragma endscop
}