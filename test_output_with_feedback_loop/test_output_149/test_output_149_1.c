#pragma ACCEL kernel

void kernel_big(double A[250][250],double C4[250][250],double sum[250])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (j = 0; j < 250; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L5}
      for (k = 0; k < 250; k++) {
        tmp += A[i][k] * C4[k][j];
      }
      sum[i] = tmp;
    }
  }
//#pragma endscop
}