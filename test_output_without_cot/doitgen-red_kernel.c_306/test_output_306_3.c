#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 30; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (j = 0; j < 30; j++) {
      sum[j] = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L2}
      for (k = 0; k < 25; k++) {
        sum[j] += A[k][j] * C4[k][i];
      }
    }
  }
//#pragma endscop
}