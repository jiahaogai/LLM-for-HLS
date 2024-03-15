
#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][24][20],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 24; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 20; p++) {
        double sum_tmp = 0.0;
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L3}
	for (s = 0; s < 30; s++) {
          sum_tmp += A[r][p][s] * C4[s][q][p];
        }
	sum[q] = sum_tmp;
      }
      for (p = 0; p < 20; p++) {
        A[r][p][0] = sum[q] + 1.0;
      }
    }
  }
//#pragma endscop
}
