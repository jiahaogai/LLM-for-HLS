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
      sum[q] = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L2}
      for (p = 0; p < 25; p++) {
        sum[q] += A[p][r][q] * C4[p][q];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  for (r = 0; r < 30; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (s = 0; s < 30; s++) {
      C4[r][s] = 0.0;
      
#pragma ACCEL PARALLEL reduction=C4 FACTOR=auto{__PARA__L5}
      for (q = 0; q < 20; q++) {
        C4[r][s] += A[q][r][s] * sum[q];
      }
    }
  }
//#pragma endscop
}