#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  double tmp;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 30; q++) {
      sum[q] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{30}
      for (p = 0; p < 25; p++) {
        tmp = A[p][0][r] * C4[p][q];
        for (s = 1; s < 20; s++) {
          tmp = tmp + A[p][s][r] * C4[p][q];
        }
        sum[q] += tmp;
      }
    }
  }
//#pragma endscop
}