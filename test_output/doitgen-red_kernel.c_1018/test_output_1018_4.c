#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  double temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 30; q++) {
      temp = A[0][0][r] * C4[0][q] + A[0][1][r] * C4[1][q] + A[0][2][r] * C4[2][q];
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L4}
      for (p = 1; p < 20; p++) {
        temp += A[p][0][r] * C4[0][q] + A[p][1][r] * C4[1][q] + A[p][2][r] * C4[2][q];
      }
      sum[r] = temp;
    }
  }
}