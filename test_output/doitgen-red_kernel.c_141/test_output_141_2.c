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
    
#pragma ACCEL TILE FACTOR=auto{4}
    for (q = 0; q < 20; q++) {
      sum[q] = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        sum[q] += A[r][q][p];
      }
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      for (s = 0; s < 30; s++) {
        A[r][q][s] = sum[q] - A[r][q][s];
      }
    }
  }
//#pragma endscop
}