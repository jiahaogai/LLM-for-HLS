#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int k;
  int q;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (k = 0; k < 20; k++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (q = 0; q < 30; q++) {
        double sum_tmp = A[r][k][q];
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L3}
	for (s = 0; s < 30; s++) {
          sum_tmp += A[r][k][s] * C4[s][q];
        }
	sum[q] = sum_tmp;
      }
      for (q = 0; q < 30; q++) {
        A[r][k][q] = sum[q];
      }
    }
  }
//#pragma endscop
}