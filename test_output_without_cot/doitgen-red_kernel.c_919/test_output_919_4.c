#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (q = 0; q < 30; q++) {
      double sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      for (p = 0; p < 25; p++) {
        sum += A[p][s][r] * C4[p][q];
      }
      C4[r][q] = sum;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (s = 0; s < 20; s++) {
      double sum_tmp = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
      for (q = 0; q < 30; q++) {
        sum_tmp += C4[r][q] * A[s][p][q];
      }
      A[s][0][r] = sum_tmp;
    }
  }
//#pragma endscop
}