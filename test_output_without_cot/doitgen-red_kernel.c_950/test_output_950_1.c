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
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (q = 0; q < 20; q++) {
      for (s = 0; s < 30; s++) {
        sum[s] = ((double )0);
      }
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      for (p = 0; p < 20; p++) {
        for (s = 0; s < 30; s++) {
          sum[s] = sum[s] + A[r][p][s] * C4[p][q];
        }
      }
      for (s = 0; s < 30; s++) {
        A[r][q][s] = sum[s];
      }
    }
  }
//#pragma endscop
}