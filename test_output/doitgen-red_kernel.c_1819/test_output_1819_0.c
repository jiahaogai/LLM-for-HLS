#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[25][25][30][35],double sum[25][35])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 25; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (p = 0; p < 30; p++) {
        double sum_tmp = ((double )0);
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{30}
	for (s = 0; s < 35; s++) {
          sum_tmp += A[r][p][s] * C4[q][r][s][p];
        }
	sum[q][p] = sum_tmp;
      }
      for (p = 0; p < 30; p++) {
        double sum_tmp = sum[q][p];
        A[q][p][0] = sum_tmp;
      }
    }
    for (p = 0; p < 30; p++) {
      double sum_tmp = ((double )0);
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{1}
      for (q = 0; q < 25; q++) {
        sum_tmp += A[q][p][0] * C4[q][r][0][p];
      }
      sum[r][0] = sum_tmp;
    }
  }
//#pragma endscop
}