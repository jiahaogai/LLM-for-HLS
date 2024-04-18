#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PIPELINE auto{flatten}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        sum[p] = 0.0;
        for (int i = 0; i < 5; i++) {
          sum[p] += A[r][q][i] * C4[i][p];
        }
      }
    }
  }
//#pragma endscop
}