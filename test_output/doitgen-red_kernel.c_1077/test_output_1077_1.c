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
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 30; q++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L4}
      for (p = 0; p < 25; p++) {
        tmp += A[p][0][r] * C4[p][q];
      }
      sum[r] = tmp;
    }
    for (s = 0; s < 30; s++) {
      C4[r][s] = sum[r] * A[24][s][q];
    }
  }
//#pragma endscop
}