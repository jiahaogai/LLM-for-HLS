#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{25}

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{25}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      double tmp = A[r][q][0];
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (p = 1; p < 30; p++) {
        tmp += A[r][q][p];
      }
      sum[q] = tmp;
    }
    
#pragma ACCEL PIPELINE auto{1}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (s = 0; s < 30; s++) {
      double tmp = C4[s][r];
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (q = 0; q < 20; q++) {
        tmp += sum[q] * C4[s][q];
      }
      C4[s][r] = tmp;
    }
  }
//#pragma endscop
}