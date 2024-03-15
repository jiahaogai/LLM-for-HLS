
8. Don't automatically distribute the middle loop across multiple processors.
9. Automatically distribute the outermost loop across 1 processors.
10. Set the auto_parallelizer's aggregate partitioning factor to 2.


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
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        double sum_tmp = 0.0;
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L3}
	for (s = 0; s < 30; s++) {
          sum_tmp += A[r][q][s] * C4[s][p];
        }
	sum[p] = sum_tmp;
      }
      for (p = 0; p < 30; p++) {
        A[r][q][p] = sum[p];
      }
    }
  }
//#pragma endscop
}
