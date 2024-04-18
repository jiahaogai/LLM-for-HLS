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
    
#pragma ACCEL TILE FACTOR=auto{4}
    for (q = 0; q < 20; q++) {
      sum[q] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      for (p = 0; p < 30; p++) {
        sum[q] += A[r][q][p] * C4[p];
      }
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (s = 0; s < 30; s++) {
      A[r][0][s] = sum[0] * C4[s];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (r_outer = 1; r_outer < 20; r_outer++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (s = 0; s < 30; s++) {
        double sum_tmp = A[r][0][s];
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L9}
	for (p = 0; p < 30; p++) {
          sum_tmp += A[r][q][p] * C4[p * 30 + s];
        }
	A[r][q][s] = sum_tmp;
      }
    }
  }
//#pragma endscop
}