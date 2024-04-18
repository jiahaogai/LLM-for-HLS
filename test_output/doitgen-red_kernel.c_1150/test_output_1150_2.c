#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[20][30][40],double sum[25][30][40])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        sum[r][p][q] = 0.0;
        for (s = 0; s < 40; s++) {
          sum[r][p][q] += A[r][q][s] * C4[q][p][s];
        }
      }
    }
  }
//#pragma endscop
}