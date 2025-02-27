#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      double tmp = A[r][q][0];
      
#pragma ACCEL PIPELINE auto{off}
      for (p = 0; p < 30; p++) {
        
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
        for (s = 0; s < 30; s++) {
          tmp += A[r][q][p] * C4[p][s];
        }
      }
      sum[q] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      A[r][q][0] = sum[q];
    }
  }
//#pragma endscop
}