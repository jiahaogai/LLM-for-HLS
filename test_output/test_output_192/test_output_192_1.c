

 #pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{off}
      for (s = 0; s < 30; s++) {
        sum[s] = 0.0;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      for (p = 0; p < 20; p++) {
        for (s = 0; s < 30; s++) {
          sum[s] += A[r][q][p] * C4[p][s];
        }
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L1}
      for (s = 0; s < 30; s++) {
        A[r][q][s] = sum[s];
      }
    }
  }
//#pragma endscop
}