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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{30}
      for (p = 0; p < 30; p++) {
        double sum_tmp = 0.0;
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
        for (s = 0; s < 30; s++) {
          sum_tmp += A[r][q][s] * C4[s][p];
        }
        sum[p] = sum_tmp;
        double A_tmp = 0.0;
        for (s = 0; s < 30; s++) {
          A_tmp += C4[s][p] * sum[s];
        }
        A[r][q][p] = A_tmp;
      }
    }
  }
//#pragma endscop
}