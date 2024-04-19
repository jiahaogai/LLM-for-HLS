#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{25}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      sum[q] = ((double )0);
    }
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
    for (p = 0; p < 20; p++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (s = 0; s < 30; s++) {
        sum[s] += A[r][p][s] * C4[p][s];
      }
    }
  }
//#pragma endscop
}