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
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 30; p++) {
        for (s = 0; s < 30; s++) {
          if (s < p) {
            A[r][q][s] = 0.0;
          }
          A[r][q][p] += C4[s][p] * A[r][q][s];
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (p = 0; p < 30; p++) {
    sum[p] = A[0][0][p] + A[0][1][p];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (p = 0; p < 30; p++) {
    for (r = 1; r < 25; r++) {
      sum[p] += A[r][19][p];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (p = 0; p < 30; p++) {
    for (s = 0; s < 30; s++) {
      for (r = 0; r < 25; r++) {
        sum[p] += A[r][19][s] * s;
      }
    }
  }
//#pragma endscop
}